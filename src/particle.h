#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
} Particle;


void initialize_random_particle(Particle *p, Vector2 start_position, Vector2 start_velocity);

void update_particle_position(Particle *p);

// draws particle that is stored in an array to windows
void draw_particle(Particle *p);


#endif
