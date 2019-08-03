//
//  MemoryMappedFile.hpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#ifndef MemoryMappedFile_hpp
#define MemoryMappedFile_hpp

#include <stdio.h>

#include "OSGlobalEnums.h"
#include "FileHandle.h"

namespace EasyLoader {
class MemoryMappedFile{
public:
    static void* Map(FileHandle* file)
    {
        return Map(file, 0, 0);
    }
    
    static void Unmap(void* address)
    {
        Unmap(address, 0);
    }
    
    static void* Map(FileHandle* file, size_t length, size_t offset);
    static void Unmap(void* address, size_t length);
#if TARGET_POSIX
    static void* Map(int fd, size_t length, size_t offset);
#endif
};
}
#endif /* MemoryMappedFile_hpp */
