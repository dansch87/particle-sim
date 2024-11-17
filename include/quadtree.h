#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <stdint.h>
#include "raylib.h"
#include "particle.h"
#include "arena.h"


typedef struct QuadTree {
    Rectangle *boundary;
    struct Particle **particles;
    int particle_count;
    int capacity;
    struct QuadTree *nw;
    struct QuadTree *ne;
    struct QuadTree *sw;
    struct QuadTree *se;
} QuadTree;


QuadTree *quadtree_create(Arena *arena, Rectangle *boundary) ;

Rectangle* CreateAABB(Arena *arena, Rectangle rect);

void quadtree_subdivide(Arena *arena, QuadTree *root);

bool quadtree_insert(Arena *arena, QuadTree *root, Particle *particle);

void quadtree_destroy(QuadTree* tree);

void quadtree_clear(QuadTree *tree);

void quadtree_draw(QuadTree* tree);

void quadtree_query(QuadTree *tree, Rectangle range, Particle **result, int *count, int maxCount);

int quadtree_element_count(QuadTree* tree);


#endif