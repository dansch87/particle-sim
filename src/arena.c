#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "arena.h"



Arena arena_init(size_t capacity) {
    char *data = (char*)malloc(sizeof(char) * capacity);
    if (data == NULL) {
        fprintf(stderr, "arena_create: malloc failed!\n");
        exit(1);
    }
    Arena arena = {
        .data = data,
        .capacity = capacity,
        .size = 0,
    };
    return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
    assert(arena->size + size < arena->capacity);
    char *data = &arena->data[arena->size];
    arena->size += size;
    return data;
}

void arena_clear(Arena *arena) {
    arena->size = 0;
}

void arena_print(Arena *arena) {
    printf("cap: %zu, size: %zu\n", arena->capacity, arena->size);
}

void arena_free(Arena *arena) {
    arena->capacity = 0;
    arena->size = 0;
    free(arena->data);
}