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
typedef wchar_t Il2CppChar;
#elif __has_feature(cxx_unicode_literals)
typedef char16_t Il2CppChar;
#else
typedef uint16_t Il2CppChar;
#endif
#if _MSC_VER
typedef wchar_t Il2CppNativeChar;
#define IL2CPP_NATIVE_STRING(str) L##str
#else
typedef char Il2CppNativeChar;
#define IL2CPP_NATIVE_STRING(str) str
#endif
#if _MSC_VER
#define IL2CPP_UNREACHABLE __assume(0)
#elif __has_builtin(__builtin_unreachable)
#define IL2CPP_UNREACHABLE __builtin_unreachable()
#else
#define IL2CPP_UNREACHABLE
#endif
#if defined(_MSC_VER)
#define IL2CPP_ZERO_LEN_ARRAY 0
#else
#define IL2CPP_ZERO_LEN_ARRAY 0
#endif

#ifdef TARGET_WIN
#include <crtdbg.h>
#define IL2CPP_ASSERT(expr) \
    _ASSERTE(expr)
#else
#define IL2CPP_ASSERT(expr) \
    assert(expr)
#endif


#define IL2CPP_MALLOC(size) il2cpp::utils::Memory::Malloc(size)
#define IL2CPP_MALLOC_ALIGNED(size, alignment) il2cpp::utils::Memory::AlignedMalloc(size, alignment)
#define IL2CPP_MALLOC_ZERO(size) il2cpp::utils::Memory::Calloc(1,size)
#define IL2CPP_FREE(memory) il2cpp::utils::Memory::Free(memory)
#define IL2CPP_FREE_ALIGNED(memory) il2cpp::utils::Memory::AlignedFree(memory)
#define IL2CPP_CALLOC(count, size) il2cpp::utils::Memory::Calloc(count,size)
#define IL2CPP_REALLOC(memory, newSize) il2cpp::utils::Memory::Realloc(memory,newSize)
#define IL2CPP_REALLOC_ALIGNED(memory, newSize, alignment) il2cpp::utils::Memory::AlignedRealloc(memory, newSize, alignment)


#endif /* OSGlobalConfig_h */
