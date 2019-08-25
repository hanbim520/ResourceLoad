//
//  MemoryMappedFile.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/25/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#ifdef  TARGET_WIN
 #include "../MemoryMappedFile.hpp"
 #include "../File.hpp"
#include "../OSGlobalConfig.h"
#include <mutex>
#include <map>
#include <Windows.h>
#include <Objidl.h>
#include <limits>

namespace EasyLoader {
	static std::mutex s_MutexMap;
	static std::mutex s_MutexUnmap;
	static std::map<void*, HANDLE> s_MappedAddressToMappedFileObject;

	void* MemoryMappedFile::Map(FileHandle* file, size_t length, size_t offset)
	{
		s_MutexMap.lock();

		HANDLE mappedFile = CreateFileMapping((HANDLE)file, NULL, PAGE_READONLY, 0, 0, NULL);
		if (mappedFile == NULL)
		{
			s_MutexMap.unlock();
			return NULL;
		}
		EaseLoad_ASSERT(offset <= (std::numeric_limits<DWORD>::max)());
		EaseLoad_ASSERT(length <= (std::numeric_limits<DWORD>::max)());

		void* address = MapViewOfFile(mappedFile, FILE_MAP_READ, 0, static_cast<DWORD>(offset), static_cast<DWORD>(length));
		if (address == NULL)
		{

			DWORD error = GetLastError();
			CloseHandle(mappedFile);
			s_MutexMap.unlock();
			return NULL;
		}

		s_MappedAddressToMappedFileObject[address] = mappedFile;

		s_MutexMap.unlock();
		return address;
	}

	void MemoryMappedFile::Unmap(void* address, size_t length)
	{
		if (address != NULL)
		{
			s_MutexUnmap.lock();

			BOOL error = UnmapViewOfFile(address);
			if (error != 0)
				s_MutexUnmap.unlock();
			EaseLoad_ASSERT(error != 0);
			(void)error; // Avoid an unused variable warning

			std::map<void*, HANDLE>::iterator entry = s_MappedAddressToMappedFileObject.find(address);
			if (entry != s_MappedAddressToMappedFileObject.end())
			{
				error = CloseHandle(entry->second);
				EaseLoad_ASSERT(error != 0);
			}
			s_MutexUnmap.unlock();
		}
	}
}

#endif