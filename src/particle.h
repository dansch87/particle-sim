#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
} Particle;


void initialize_particle(Particle *p, Vector2 start_position, Vector2 start_velocity, float radius);

void update_particle_position(Particle *p);

// draws particle that is stored in an array to windows
void draw_particle(Particle *p);

void check_collision_window(Particle *p, int wwin_width, int win_height);

#endif
