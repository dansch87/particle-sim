#ifndef KDTREE_H
#define KDTREE_H

#include "raylib.h"
#include "particle.h"

typedef struct kdnode {
    Vector2 position;
    struct kdnode *left;
    struct kdnode *right;
    int axis; // 0 for x, 1 for y
} KDNode;

KDNode *kdtree_insert(KDNode *node, Vector2 position, int depth);

void kdtree_free(KDNode *node);

KDNode *kdtree_build(Particle *particles, int num_particles);

#endif
