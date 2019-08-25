//
//  OSGlobalConfig.h
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#ifndef OSGlobalConfig_h
#define OSGlobalConfig_h
#include <assert.h>
#include "./Utils/Memory.h"

// #define TARGET_UNIX (TARGET_LINUX || TARGET_ANDROID  || TARGET_IOS)
// #define TARGET_WIN (TARGET_WIN32)

#if _MSC_VER
typedef wchar_t EasyCppChar;
#elif __has_feature(cxx_unicode_literals)
typedef char16_t EasyCppChar;
#else
typedef uint16_t EasyCppChar;
#endif
#if _MSC_VER
typedef wchar_t EasyCppNativeChar;
#define EasyLoad_NATIVE_STRING(str) L##str
#else
typedef char EasyCppNativeChar;
#define EasyLoad_NATIVE_STRING(str) str
#endif
#if _MSC_VER
#define EasyLoad_UNREACHABLE __assume(0)
#elif __has_builtin(__builtin_unreachable)
#define EasyLoad_UNREACHABLE __builtin_unreachable()
#else
#define EasyLoad_UNREACHABLE
#endif
#if defined(_MSC_VER)
#define EasyLoad_ZERO_LEN_ARRAY 0
#else
#define EasyLoad_ZERO_LEN_ARRAY 0
#endif

#ifdef TARGET_WIN
#include <crtdbg.h>
#define EasyLoad_ASSERT(expr) \
    _ASSERTE(expr)
#else
#define EasyLoad_ASSERT(expr) \
    assert(expr)
#endif


#define EasyLoad_MALLOC(size) EasyLoad::utils::Memory::Malloc(size)
#define EasyLoad_MALLOC_ALIGNED(size, alignment) EasyLoad::utils::Memory::AlignedMalloc(size, alignment)
#define EasyLoad_MALLOC_ZERO(size) EasyLoad::utils::Memory::Calloc(1,size)
#define EasyLoad_FREE(memory) EasyLoad::utils::Memory::Free(memory)
#define EasyLoad_FREE_ALIGNED(memory) EasyLoad::utils::Memory::AlignedFree(memory)
#define EasyLoad_CALLOC(count, size) EasyLoad::utils::Memory::Calloc(count,size)
#define EasyLoad_REALLOC(memory, newSize) EasyLoad::utils::Memory::Realloc(memory,newSize)
#define EasyLoad_REALLOC_ALIGNED(memory, newSize, alignment) EasyLoad::utils::Memory::AlignedRealloc(memory, newSize, alignment)


#endif /* OSGlobalConfig_h */
