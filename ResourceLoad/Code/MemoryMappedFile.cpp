//
//  MemoryMappedFile.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#ifdef  TARGET_UNIX
#include "MemoryMappedFile.hpp"

#include <mutex>
#include <map>
#include <fcntl.h>
#include <sys/mman.h>

#include "File.hpp"

namespace EasyLoader {

static std::mutex s_MutexMap;
static std::mutex s_MutexUnmap;
#ifdef TARGET_POSIX
    static std::mutex s_MutexPostMap;
#endif
static std::map<void*, int64_t> s_MappedAddressToMappedLength;

void* MemoryMappedFile::Map(FileHandle* file, size_t length, size_t offset)
{
    s_MutexMap.lock();
    
    if (length == 0)
    {
        int error = 0;
        length = File::GetLength(file, &error);
        if (error != 0)
        {
            s_MutexMap.unlock();
            return NULL;
        }
    }
    
    void* address = mmap(NULL, length, PROT_READ, MAP_FILE | MAP_PRIVATE, file->fd, offset);
    if ((intptr_t)address == -1)
    {
        s_MutexMap.unlock();
        return NULL;
    }
    s_MutexMap.unlock();
    s_MappedAddressToMappedLength[address] = length;
   
    
    return address;
}

#ifdef TARGET_POSIX
void* MemoryMappedFile::Map(int fd, size_t length, size_t offset)
{
    s_MutexPostMap.lock();
    void* address = mmap(NULL, length, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, offset);
    if ((intptr_t)address == -1)
    {
        s_MutexPostMap.unlock();
        return NULL;
    }

    s_MappedAddressToMappedLength[address] = length;
    s_MutexPostMap.unlock();
    return address;
}
#endif

void MemoryMappedFile::Unmap(void* address, size_t length)
{
    s_MutexUnmap.lock();
    
    if (length == 0)
    {
        std::map<void*, int64_t>::iterator entry = s_MappedAddressToMappedLength.find(address);
        if (entry != s_MappedAddressToMappedLength.end())
            length = entry->second;
    }
    
    int error = munmap(address, length);
     s_MutexUnmap.unlock();
    assert(error == 0);
   (void)error; // Avoid an unused variable warning
}
}

#endif