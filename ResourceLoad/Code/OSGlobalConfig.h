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
#define EaseLoad_NATIVE_STRING(str) L##str
#else
typedef char EasyCppNativeChar;
#define EaseLoad_NATIVE_STRING(str) str
#endif
#if _MSC_VER
#define EaseLoad_UNREACHABLE __assume(0)
#elif __has_builtin(__builtin_unreachable)
#define EaseLoad_UNREACHABLE __builtin_unreachable()
#else
#define EaseLoad_UNREACHABLE
#endif
#if defined(_MSC_VER)
#define EaseLoad_ZERO_LEN_ARRAY 0
#else
#define EaseLoad_ZERO_LEN_ARRAY 0
#endif

#ifdef TARGET_WIN
#include <crtdbg.h>
#define EaseLoad_ASSERT(expr) \
    _ASSERTE(expr)
#else
#define EaseLoad_ASSERT(expr) \
    assert(expr)
#endif


#define EaseLoad_MALLOC(size) EaseLoad::utils::Memory::Malloc(size)
#define EaseLoad_MALLOC_ALIGNED(size, alignment) EaseLoad::utils::Memory::AlignedMalloc(size, alignment)
#define EaseLoad_MALLOC_ZERO(size) EaseLoad::utils::Memory::Calloc(1,size)
#define EaseLoad_FREE(memory) EaseLoad::utils::Memory::Free(memory)
#define EaseLoad_FREE_ALIGNED(memory) EaseLoad::utils::Memory::AlignedFree(memory)
#define EaseLoad_CALLOC(count, size) EaseLoad::utils::Memory::Calloc(count,size)
#define EaseLoad_REALLOC(memory, newSize) EaseLoad::utils::Memory::Realloc(memory,newSize)
#define EaseLoad_REALLOC_ALIGNED(memory, newSize, alignment) EaseLoad::utils::Memory::AlignedRealloc(memory, newSize, alignment)


#endif /* OSGlobalConfig_h */
