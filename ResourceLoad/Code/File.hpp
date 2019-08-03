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
   
    
   static FileHandle* Open(const std::string& path, int mode, int accessMode, int shareMode, int options, int *error);
   static bool Close(FileHandle* handle, int *error);
};
}
#endif /* File_hpp */
