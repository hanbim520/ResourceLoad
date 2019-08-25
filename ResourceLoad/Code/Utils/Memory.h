//
//  Memory.h
//  ResourceLoad
//
//  Created by 张海军 on 8/25/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#pragma once

namespace EasyLoad
{
namespace utils
{
	typedef struct
	{
		void* (*malloc_func)(size_t size);
		void* (*aligned_malloc_func)(size_t size, size_t alignment);
		void(*free_func)(void *ptr);
		void(*aligned_free_func)(void *ptr);
		void* (*calloc_func)(size_t nmemb, size_t size);
		void* (*realloc_func)(void *ptr, size_t size);
		void* (*aligned_realloc_func)(void *ptr, size_t size, size_t alignment);
	} EasyLoadMemoryCallbacks;

    struct Memory
    {
        static void SetMemoryCallbacks(EasyLoadMemoryCallbacks* callbacks);

        static void* Malloc(size_t size);
        static void* AlignedMalloc(size_t size, size_t alignment);
        static void Free(void* memory);
        static void AlignedFree(void* memory);
        static void* Calloc(size_t count, size_t size);
        static void* Realloc(void* memory, size_t newSize);
        static void* AlignedRealloc(void* memory, size_t newSize, size_t alignment);
    };
	
} /* namespace utils */
} /* namespace EasyLoad */

#define EasyLoad_MALLOC(size) EasyLoad::utils::Memory::Malloc(size)
#define EasyLoad_MALLOC_ALIGNED(size, alignment) EasyLoad::utils::Memory::AlignedMalloc(size, alignment)
#define EasyLoad_MALLOC_ZERO(size) EasyLoad::utils::Memory::Calloc(1,size)
#define EasyLoad_FREE(memory) EasyLoad::utils::Memory::Free(memory)
#define EasyLoad_FREE_ALIGNED(memory) EasyLoad::utils::Memory::AlignedFree(memory)
#define EasyLoad_CALLOC(count, size) EasyLoad::utils::Memory::Calloc(count,size)
#define EasyLoad_REALLOC(memory, newSize) EasyLoad::utils::Memory::Realloc(memory,newSize)
#define EasyLoad_REALLOC_ALIGNED(memory, newSize, alignment) EasyLoad::utils::Memory::AlignedRealloc(memory, newSize, alignment)
