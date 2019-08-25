#pragma once

namespace EaseLoad
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
	} EaseLoadMemoryCallbacks;

    struct Memory
    {
        static void SetMemoryCallbacks(EaseLoadMemoryCallbacks* callbacks);

        static void* Malloc(size_t size);
        static void* AlignedMalloc(size_t size, size_t alignment);
        static void Free(void* memory);
        static void AlignedFree(void* memory);
        static void* Calloc(size_t count, size_t size);
        static void* Realloc(void* memory, size_t newSize);
        static void* AlignedRealloc(void* memory, size_t newSize, size_t alignment);
    };
	
} /* namespace utils */
} /* namespace EaseLoad */

#define EaseLoad_MALLOC(size) EaseLoad::utils::Memory::Malloc(size)
#define EaseLoad_MALLOC_ALIGNED(size, alignment) EaseLoad::utils::Memory::AlignedMalloc(size, alignment)
#define EaseLoad_MALLOC_ZERO(size) EaseLoad::utils::Memory::Calloc(1,size)
#define EaseLoad_FREE(memory) EaseLoad::utils::Memory::Free(memory)
#define EaseLoad_FREE_ALIGNED(memory) EaseLoad::utils::Memory::AlignedFree(memory)
#define EaseLoad_CALLOC(count, size) EaseLoad::utils::Memory::Calloc(count,size)
#define EaseLoad_REALLOC(memory, newSize) EaseLoad::utils::Memory::Realloc(memory,newSize)
#define EaseLoad_REALLOC_ALIGNED(memory, newSize, alignment) EaseLoad::utils::Memory::AlignedRealloc(memory, newSize, alignment)
