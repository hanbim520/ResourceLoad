//
//  File.hpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>

#include "FileHandle.h"
#include "ErrorCode.h"

namespace EasyLoader {

class File{
public:
    static  int64_t GetLength(FileHandle* handle, int *error);
    static  ErrorCode FileErrnoToErrorCode(int32_t code);
    static  ErrorCode PathErrnoToErrorCode(const std::string& path, int32_t code);
   
	static UnityPalFileAttributes GetFileAttributesEX(const std::string& path, int* error);
    
    static FileHandle* Open(const std::string& path, int mode, int accessMode, int shareMode, int options, int *error);
    static bool Close(FileHandle* handle, int *error);
    static int Read(FileHandle* handle, char *dest, int count, int *error);
    static int32_t Write(FileHandle* handle, const char* buffer, int count, int *error);
    static bool Flush(FileHandle* handle, int* error);
    static void Lock(FileHandle* handle, int64_t position, int64_t length, int* error);
    static void Unlock(FileHandle* handle, int64_t position, int64_t length, int* error);
    static bool SetLength(FileHandle* handle, int64_t length, int *error);
    static int64_t Seek(FileHandle* handle, int64_t offset, int origin, int *error);
};
}
#endif /* File_hpp */
