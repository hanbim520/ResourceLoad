//
//  OSGlobalEnums.h
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#ifndef OSGlobalEnums_h
#define OSGlobalEnums_h
namespace EasyLoader {
typedef enum
{
    kFileTypeUnknown = 0x0000,
    kFileTypeDisk = 0x0001,
    kFileTypeChar = 0x0002,
    kFileTypePipe = 0x0003,
    kFileTypeRemote = 0x8000
} FileType;

typedef enum
{
    kFileAttributeReadOnly = 0x00000001,
    kFileAttributeHidden = 0x00000002,
    kFileAttributeSystem = 0x00000004,
    kFileAttributeDirectory = 0x00000010,
    kFileAttributeArchive = 0x00000020,
    kFileAttributeDevice = 0x00000040,
    kFileAttributeNormal = 0x00000080,
    kFileAttributeTemporary = 0x00000100,
    kFileAttributeSparse_file = 0x00000200,
    kFileAttributeReparse_point = 0x00000400,
    kFileAttributeCompressed = 0x00000800,
    kFileAttributeOffline = 0x00001000,
    kFileAttributeNot_content_indexed = 0x00002000,
    kFileAttributeEncrypted = 0x00004000,
    kFileAttributeVirtual = 0x00010000,
    kFileAttributeInternalChangeExecutable = 0x80000000 // Only used internally by Change
} UnityPalFileAttributes;

typedef enum
{
    kFileAccessRead = 0x01,
    kFileAccessWrite = 0x02,
    kFileAccessReadWrite = kFileAccessRead | kFileAccessWrite
} FileAccess;

typedef enum
{
    kFileModeCreateNew = 1,
    kFileModeCreate = 2,
    kFileModeOpen = 3,
    kFileModeOpenOrCreate = 4,
    kFileModeTruncate = 5,
    kFileModeAppend = 6
} FileMode;

typedef enum
{
    kFileShareNone = 0x0,
    kFileShareRead = 0x01,
    kFileShareWrite = 0x02,
    kFileShareReadWrite = kFileShareRead | kFileShareWrite,
    kFileShareDelete = 0x04
} FileShare;

typedef enum
{
    kFileOptionsNone = 0,
    kFileOptionsTemporary = 1,  // Internal.   See note in System.IO.FileOptions
    kFileOptionsEncrypted = 0x4000,
    kFileOptionsDeleteOnClose = 0x4000000,
    kFileOptionsSequentialScan = 0x8000000,
    kFileOptionsRandomAccess = 0x10000000,
    kFileOptionsAsynchronous = 0x40000000,
    kFileOptionsWriteThrough = 0x80000000
} FileOptions;

typedef enum
{
    kFileSeekOriginBegin = 0,
    kFileSeekOriginCurrent = 1,
    kFileSeekOriginEnd = 2
} SeekOrigin;

}
#endif /* OSGlobalEnums_h */
