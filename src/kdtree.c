#include <stdlib.h>

#include "kdtree.h"
#include "raylib.h"
#include "particle.h"



KDNode *kdtree_insert(KDNode *node, Vector2 position, int depth) {
    if (node == NULL) {
        KDNode *new_node = malloc(sizeof(KDNode));
        new_node->position = position;
        new_node->left = NULL;
        new_node->right= NULL;
        new_node->axis = depth % 2; // alternate between x and y
        return new_node;
    }

    int axis = node->axis;
    if ((axis == 0 && position.x < node->position.x) || (axis == 1 && position.y < node->position.y)) {
        node->left = kdtree_insert(node->left, position, depth + 1);
    } else {
        node->right = kdtree_insert(node->right, position, depth + 1);
    }
    return node;
}

void kdtree_free(KDNode *node) {
    if (node == NULL) {
        return;
    }
    kdtree_free(node->left);
    kdtree_free(node->right);
    free(node);
}

KDNode *kdtree_build(Particle *particles, int num_particles) {
    KDNode *root = NULL;
    for (int i = 0; i < num_particles; i++) {
        root = kdtree_insert(root, particles[i].position, 0);
    }
    return root;
}
