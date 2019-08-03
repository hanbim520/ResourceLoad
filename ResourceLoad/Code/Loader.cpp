//
//  Loader.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#include "Loader.hpp"
#include "FileHandle.h"
#include "MemoryMappedFile.hpp"
#include "File.hpp"
namespace EasyLoader {
void* Loader::LoadMetadataFile(const char* fileName)
{
    
    int error = 0;
    FileHandle* handle = File::Open(fileName, kFileModeOpen, kFileAccessRead, kFileShareRead, kFileOptionsNone, &error);
    if (error != 0)
        return NULL;
    
    void* fileBuffer = MemoryMappedFile::Map(handle);
    
    File::Close(handle, &error);
    if (error != 0)
    {
        MemoryMappedFile::Unmap(fileBuffer);
        fileBuffer = NULL;
        return NULL;
    }
    
    return fileBuffer;
}
}
