//
//  FileHandle.h
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#ifndef FileHandle_h
#define FileHandle_h
#include <string>
#ifdef TARGET_UNIX
#include <sys/types.h>
#endif
#include "OSGlobalEnums.h"

namespace EasyLoader {
struct FileHandle
{
    int fd;
    FileType type;
    std::string path;
    int options;
    int shareMode;
    int accessMode;
    
    // device and inode are used as key for finding file handles
    dev_t device;
    ino_t inode;
    
    // Linked list of file handles
    FileHandle *prev;
    FileHandle *next;
    
    FileHandle() : prev(NULL), next(NULL)
    {
    }
};
struct MapHandle
{
	int length;
	void* ptr;
};
}
#endif /* FileHandle_h */
