//
//  Memory.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/25/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#include "Memory.h"
#include <string>

namespace EaseLoad
{
namespace utils
{
	namespace EasyLoader {
		namespace Memory
		{
			void* AlignedAlloc(size_t size, size_t alignment);
			void* AlignedReAlloc(void* memory, size_t newSize, size_t alignment);
			void AlignedFree(void* memory);
		}
		namespace Memory
		{
			void* AlignedAlloc(size_t size, size_t alignment)
			{
				return _aligned_malloc(size, alignment);
			}

			void* AlignedReAlloc(void* memory, size_t newSize, size_t alignment)
			{
				return _aligned_realloc(memory, newSize, alignment);
			}

			void AlignedFree(void* memory)
			{
				return _aligned_free(memory);
			}
		}
	}
	
    static EaseLoadMemoryCallbacks s_Callbacks =
    {
        malloc,
		EasyLoader::Memory::AlignedAlloc,
        free,
	    EasyLoader::Memory::AlignedFree,
        calloc,
        realloc,
		EasyLoader::Memory::AlignedReAlloc
    };

    void Memory::SetMemoryCallbacks(EaseLoadMemoryCallbacks* callbacks)
    {
        memcpy(&s_Callbacks, callbacks, sizeof(EaseLoadMemoryCallbacks));
    }

    void* Memory::Malloc(size_t size)
    {
        return s_Callbacks.malloc_func(size);
    }

    void* Memory::AlignedMalloc(size_t size, size_t alignment)
    {
        return s_Callbacks.aligned_malloc_func(size, alignment);
    }

    void Memory::Free(void* memory)
    {
        return s_Callbacks.free_func(memory);
    }

    void Memory::AlignedFree(void* memory)
    {
        return s_Callbacks.aligned_free_func(memory);
    }

    void* Memory::Calloc(size_t count, size_t size)
    {
        return s_Callbacks.calloc_func(count, size);
    }

    void* Memory::Realloc(void* memory, size_t newSize)
    {
        return s_Callbacks.realloc_func(memory, newSize);
    }

    void* Memory::AlignedRealloc(void* memory, size_t newSize, size_t alignment)
    {
        return s_Callbacks.aligned_realloc_func(memory, newSize, alignment);
    }
} /* namespace utils */
} /* namespace EaseLoad */
