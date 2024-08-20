#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

typedef uint8_t Ubyte;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t SByte;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

#define MALLOC_BACKEND 0
#define VIRTUAL_ALLOC_BACKEND 1

#ifndef ARENA_ASSERT
	#define ARENA_ASSERT(c) assert(c)
#endif

#ifndef ALLOC_BACKEND
	#define ALLOC_BACKEND MALLOC_BACKEND
#endif // ALLOC_BACKEND

typedef struct ArenaAllocator ArenaAllocator;
struct ArenaAllocator {
	size_t pos;
	size_t cap;
	uintptr_t *mem;
};

#if ALLOC_BACKEND == MALLOC_BACKEND

ArenaAllocator *arena_init(size_t capacity)
{
	ArenaAllocator *aa = (ArenaAllocator *)malloc(sizeof(ArenaAllocator));
	aa->pos = 0;
	aa->cap = capacity;
	aa->mem = (uintptr_t *)malloc(capacity);

	return aa;
}

#elif ALLOC_BACKEND == VIRTUAL_ALLOC_BACKEND

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

ArenaAllocator *arena_init(size_t capacity)
{
	ArenaAllocator *aa = (ArenaAllocator *)malloc(sizeof(ArenaAllocator));
	aa->pos = 0;
	aa->cap = capacity;
	aa->mem = VirtualAllocEx(
		GetCurrentProcess(),
		NULL,
		capacity,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE
	);

	return aa;
}

#else

#error Win32 platform not found

#endif

#endif

void *arena_push(ArenaAllocator *arena, size_t size)
{
	ARENA_ASSERT(arena->pos + size <= arena->cap);

	void *mem_to_alloc = arena->mem;

	arena->pos += size;
	arena->mem += arena->pos;

	return (mem_to_alloc);
}

void arena_reset(ArenaAllocator *arena)
{
	arena->mem -= arena->pos;
	arena->pos = 0;
}

void arena_pop(ArenaAllocator *arena, size_t amount)
{
	arena->pos -= amount;
	arena->mem -= arena->pos;
}

void arena_free(ArenaAllocator *arena)
{
	arena->pos = 0;
	arena->cap = 0;
	free(arena->mem);
	free(arena);
}

#endif