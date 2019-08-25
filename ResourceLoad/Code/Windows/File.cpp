//
//  File.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#ifdef  TARGET_WIN
#include "../File.hpp"
#include "../Utils/StringUtils.h"
#include "../OSGlobalEnums.h"
#include "../OSGlobalConfig.h"

#include <Windows.h>
#include <Objidl.h>
#include <assert.h>
#include <stdint.h>
#include <minwindef.h>

#define INVALID_FILE_HANDLE     (FileHandle*)-1;


namespace EasyLoader {
	typedef std::basic_string<Il2CppChar> UTF16String;
	typedef std::basic_string<Il2CppNativeChar> Il2CppNativeString;

	static inline int Win32ErrorToErrorCode(DWORD win32ErrorCode)
	{
		return win32ErrorCode;
	}
	static inline int MonoToWindowsOpenMode(int monoOpenMode)
	{
		switch (monoOpenMode)
		{
		case kFileModeCreateNew:
			return CREATE_NEW;

		case kFileModeCreate:
			return CREATE_ALWAYS;

		case kFileModeOpen:
			return OPEN_EXISTING;

		case kFileModeOpenOrCreate:
		case kFileModeAppend:
			return OPEN_ALWAYS;

		case kFileModeTruncate:
			return TRUNCATE_EXISTING;

		default:
			assert(false && "Unknown mono open mode");
			IL2CPP_UNREACHABLE;
		}
	}

	static inline int MonoToWindowsAccessMode(int monoAccessMode)
	{
		switch (monoAccessMode)
		{
		case kFileAccessRead:
			return GENERIC_READ;

		case kFileAccessWrite:
			return GENERIC_WRITE;

		case kFileAccessReadWrite:
			return GENERIC_READ | GENERIC_WRITE;

		default:
			return 0;
		}
	}
	static inline DWORD MonoOptionsToWindowsFlagsAndAttributes(const std::string& path, int options)
	{
		DWORD flagsAndAttributes;

		if (options & kFileOptionsEncrypted)
		{
			flagsAndAttributes = FILE_ATTRIBUTE_ENCRYPTED;
		}
		else
		{
			flagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
		}

		// Temporary flag does not mean temporary file.
		flagsAndAttributes |= options & ~(kFileOptionsEncrypted | kFileOptionsTemporary);

		int error;
		UnityPalFileAttributes currentAttributes = EasyLoader::File::GetFileAttributesEX(path, &error);

		if (currentAttributes != INVALID_FILE_ATTRIBUTES && (currentAttributes & FILE_ATTRIBUTE_DIRECTORY))
			flagsAndAttributes |= FILE_FLAG_BACKUP_SEMANTICS; // Required to open a directory

		return flagsAndAttributes;
	}
	UnityPalFileAttributes  File::GetFileAttributesEX(const std::string& path, int *error)
	{
		const UTF16String utf16Path(il2cpp::utils::StringUtils::Utf8ToUtf16(path.c_str()));
		WIN32_FILE_ATTRIBUTE_DATA fileAttributes;

		BOOL result = ::GetFileAttributesExW((LPCWSTR)utf16Path.c_str(), GetFileExInfoStandard, &fileAttributes);
		if (result == FALSE)
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return static_cast<UnityPalFileAttributes>(INVALID_FILE_ATTRIBUTES);
		}

		*error = kErrorCodeSuccess;
		return static_cast<UnityPalFileAttributes>(fileAttributes.dwFileAttributes);
	}
	int64_t File::GetLength(FileHandle* handle, int *error)
	{
		*error = kErrorCodeSuccess;
		LARGE_INTEGER size;
		if (!::GetFileSizeEx((HANDLE)handle, &size))
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return 0;
		}
		return size.QuadPart;
	}

	FileHandle* File::Open(const std::string& path, int openMode, int accessMode, int shareMode, int options, int *error)
	{
		const UTF16String utf16Path(il2cpp::utils::StringUtils::Utf8ToUtf16(path.c_str()));

		openMode = MonoToWindowsOpenMode(openMode);
		accessMode = MonoToWindowsAccessMode(accessMode);
		DWORD flagsAndAttributes = MonoOptionsToWindowsFlagsAndAttributes(path, options);

		HANDLE handle = ::CreateFileW((LPCWSTR)utf16Path.c_str(), accessMode, shareMode, NULL, openMode, flagsAndAttributes, NULL);

		if (INVALID_HANDLE_VALUE == handle)
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return (FileHandle*)INVALID_HANDLE_VALUE;
		}

		*error = kErrorCodeSuccess;
		return (FileHandle*)handle;
	}

	bool File::Close(FileHandle* handle, int *error)
	{
		*error = kErrorCodeSuccess;
		if (CloseHandle((HANDLE)handle))
			return true;

		*error = Win32ErrorToErrorCode(::GetLastError());
		return false;
	}
	int File::Read(FileHandle* handle, char *dest, int count, int *error)
	{
		*error = kErrorCodeSuccess;
		DWORD bytesRead = 0;
		if (!::ReadFile(handle, dest, count, &bytesRead, NULL))
			*error = Win32ErrorToErrorCode(::GetLastError());

#if IL2CPP_ENABLE_PROFILER
		IL2CPP_VM_PROFILE_FILEIO(IL2CPP_PROFILE_FILEIO_READ, count);
#endif

		return bytesRead;
	}

	int32_t File::Write(FileHandle* handle, const char* buffer, int count, int *error)
	{
		int32_t result;
		int32_t written;

		result = WriteFile((HANDLE)handle, buffer, count, (LPDWORD)&written, NULL);

		/*if (!result)
		{
			*error = GetLastError ();
			return -1;
		}*/
#if IL2CPP_ENABLE_PROFILER
		IL2CPP_VM_PROFILE_FILEIO(IL2CPP_PROFILE_FILEIO_WRITE, count);
#endif

		return written;
	}

	bool File::Flush(FileHandle* handle, int* error)
	{
		*error = kErrorCodeSuccess;
		if (FlushFileBuffers((HANDLE)handle))
			return true;

		*error = Win32ErrorToErrorCode(::GetLastError());

		return false;
	}

	void File::Lock(FileHandle* handle, int64_t position, int64_t length, int* error)
	{
		*error = kErrorCodeSuccess;

		OVERLAPPED overlapped;
		ZeroMemory(&overlapped, sizeof(overlapped));

		overlapped.Offset = position & 0xFFFFFFFF;
		overlapped.OffsetHigh = position >> 32;

		LARGE_INTEGER lengthUnion;
		lengthUnion.QuadPart = length;

		if (!::LockFileEx((HANDLE)handle, LOCKFILE_FAIL_IMMEDIATELY, 0, lengthUnion.LowPart, lengthUnion.HighPart, &overlapped))
			*error = Win32ErrorToErrorCode(::GetLastError());
	}

	void File::Unlock(FileHandle* handle, int64_t position, int64_t length, int* error)
	{
		*error = kErrorCodeSuccess;

		OVERLAPPED overlapped;
		ZeroMemory(&overlapped, sizeof(overlapped));

		overlapped.Offset = position & 0xFFFFFFFF;
		overlapped.OffsetHigh = position >> 32;

		LARGE_INTEGER lengthUnion;
		lengthUnion.QuadPart = length;

		if (!::UnlockFileEx((HANDLE)handle, 0, lengthUnion.LowPart, lengthUnion.HighPart, &overlapped))
			*error = Win32ErrorToErrorCode(::GetLastError());
	}


	bool File::SetLength(FileHandle* handle, int64_t length, int *error)
	{
		*error = kErrorCodeSuccess;
		LARGE_INTEGER zeroOffset = { 0 };
		LARGE_INTEGER requestedOffset = { 0 };
		requestedOffset.QuadPart = length;
		LARGE_INTEGER initialPosition = { 0 };

		// set position to 0 from current to retrieve current position
		if (!::SetFilePointerEx((HANDLE)handle, zeroOffset, &initialPosition, FILE_CURRENT))
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return false;
		}

		// seek to requested length
		if (!::SetFilePointerEx((HANDLE)handle, requestedOffset, NULL, FILE_BEGIN))
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return false;
		}

		// set requested length
		if (!::SetEndOfFile((HANDLE)handle))
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return false;
		}

		// restore original position
		if (!::SetFilePointerEx((HANDLE)handle, initialPosition, NULL, FILE_BEGIN))
		{
			*error = Win32ErrorToErrorCode(::GetLastError());
			return false;
		}

		return true;
	}

	int64_t File::Seek(FileHandle* handle, int64_t offset, int origin, int *error)
	{
		*error = kErrorCodeSuccess;
		LARGE_INTEGER distance;
		distance.QuadPart = offset;
		LARGE_INTEGER position = { 0 };
		if (!::SetFilePointerEx((HANDLE)handle, distance, &position, origin))
			*error = Win32ErrorToErrorCode(::GetLastError());

		return position.QuadPart;
	}
}

#endif  