#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "raylib.h"
#include "quadtree.h"
#include "config.h"



QuadTree *quadtree_create(Rectangle *boundary) {
    QuadTree *tree = (QuadTree*)malloc(sizeof(QuadTree));
    if (tree == NULL) {
        fprintf(stderr, "Failed to allocate memory for QuadTree.\n");
        exit(1);
    }
    tree->boundary = boundary;

    tree->particles = (Particle**)malloc(sizeof(Particle*) * MAX_CAPACITY_QUAD);
    if (tree->particles == NULL) {
        fprintf(stderr, "Failed to allocate memory for tree->particles.\n");
        free(tree);
        exit(1);
    }
    for (int i = 0; i < MAX_CAPACITY_QUAD; i++) {
        tree->particles[i] = NULL;
    }

    tree->particle_count = 0;
    tree->capacity = MAX_CAPACITY_QUAD;  

    tree->nw = NULL;
    tree->ne = NULL;
    tree->sw = NULL;
    tree->se = NULL;

    return tree;
}

Rectangle* CreateAABB(Rectangle rect) {
    Rectangle *aabb = (Rectangle*)malloc(sizeof(Rectangle));
    if (aabb == NULL) {
        fprintf(stdin, "Failed to allocate memory for AABB.\n");
        exit(1);
    }
    aabb->x = rect.x;
    aabb->y = rect.y;
    aabb->height = rect.height;
    aabb->width = rect.width;
    
    return aabb;
}

void quadtree_subdivide(QuadTree *root) {
    float halfWidth = root->boundary->width / 2;
    float halfHeight = root->boundary->height / 2;
    float x = root->boundary->x;
    float y = root->boundary->y;

    root->nw = quadtree_create(CreateAABB((Rectangle){x, y, halfWidth, halfHeight}));
    root->ne = quadtree_create(CreateAABB((Rectangle){x + halfWidth, y, halfWidth, halfHeight}));
    root->sw = quadtree_create(CreateAABB((Rectangle){x, y + halfHeight, halfWidth, halfHeight}));
    root->se = quadtree_create(CreateAABB((Rectangle){x + halfWidth, y + halfHeight, halfWidth, halfHeight}));
}

bool quadtree_insert(QuadTree *root, Particle *particle) {
    if (!CheckCollisionPointRec(particle->position, *(root)->boundary)) {
        return false;
    }
       
    if (root->particle_count < MAX_CAPACITY_QUAD && root->nw == NULL) {
        root->particles[root->particle_count++] = particle;
        return true;
    }

    if (root->nw == NULL) {
        quadtree_subdivide(root);
    }

    if (quadtree_insert(root->nw, particle)) return true;
    if (quadtree_insert(root->ne, particle)) return true;
    if (quadtree_insert(root->sw, particle)) return true;
    if (quadtree_insert(root->se, particle)) return true;

    return false;
}



void quadtree_destroy(QuadTree* tree) {
    if (tree == NULL) return;
    free(tree->boundary);
    free(tree->particles);
    quadtree_destroy(tree->nw);
    quadtree_destroy(tree->ne);
    quadtree_destroy(tree->sw);
    quadtree_destroy(tree->se);
    free(tree);
}

void quadtree_clear(QuadTree *tree) {
    if (tree == NULL) {
        return;
    }

    for (int i = 0; i < MAX_CAPACITY_QUAD; i++) {
        tree->particles[i] = NULL;
    }

    tree->particle_count = 0;

    // Clear sub quads recursively
    if (tree->nw != NULL) {
        quadtree_clear(tree->nw);
        quadtree_clear(tree->ne);
        quadtree_clear(tree->sw);
        quadtree_clear(tree->se);

        tree->nw = NULL;
        tree->ne = NULL;
        tree->sw = NULL;
        tree->se = NULL;
    }
}

void quadtree_draw(QuadTree* tree) {

    if (tree == NULL) {
        return;
    }
    // Draw boundary for current node
    DrawRectangleLinesEx(*(tree->boundary), 0.5, QUAD_TREE_COLOR);
    
    // Draw boudnaries for sub nodes
    if (tree->nw != NULL) {
        quadtree_draw(tree->nw);
        quadtree_draw(tree->ne);
        quadtree_draw(tree->sw);
        quadtree_draw(tree->se);
    }
}

void quadtree_query(QuadTree *tree, Rectangle range, Particle **result, int *count, int maxCount) {
    if (tree == NULL || !CheckCollisionRecs(*(tree->boundary), range)) {
        return;
    }

    // Überprüfe Partikel im aktuellen Knoten
    for (int i = 0; i < tree->particle_count; i++) {
        if (*count >= maxCount) {
            return; // Verhindert Überlauf des result-Arrays
        }
        if (CheckCollisionPointRec(tree->particles[i]->position, range)) {
            result[*count] = tree->particles[i];
            (*count)++;
        }
    }

    // Wenn es keine Unterquadranten gibt, beende hier
    if (tree->nw == NULL) {
        return;
    }

    // Rekursiv in Unterquadranten suchen
    quadtree_query(tree->nw, range, result, count, maxCount);
    quadtree_query(tree->ne, range, result, count, maxCount);
    quadtree_query(tree->sw, range, result, count, maxCount);
    quadtree_query(tree->se, range, result, count, maxCount);
}

int quadtree_element_count(QuadTree* tree) {
    if (tree == NULL) return 0;
    int count = tree->particle_count;
    if (tree->nw != NULL) {
        count += quadtree_element_count(tree->nw);
        count += quadtree_element_count(tree->ne);
        count += quadtree_element_count(tree->sw);
        count += quadtree_element_count(tree->se);
    }
    return count;
}