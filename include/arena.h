#ifndef ARENA_H_
#define ARENA_H_

#include <stdlib.h>

#define MB (1024 * 1024)
#define GB (MB * 1024)

typedef struct Arena {
    char *data;
    size_t capacity;
    size_t size;
} Arena;

Arena arena_init(size_t capacity);

void *arena_alloc(Arena *arena, size_t size);

void arena_clear(Arena *arena);

void arena_print(Arena *arena);

void arena_free(Arena *arena);

#endif