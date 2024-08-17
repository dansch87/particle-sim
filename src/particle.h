#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct {
    // Holds the linear position of the particle in world space.
    Vector2 position;
    // Holds the linear velocity of the particle in world space.
    Vector2 velocity;
    // Holds the radius of the circle particle.
    float radius;
    /*
     * Holds the acceleration of the particle. This value
     * can be used to set acceleration due to gravity (its primary
     * use), or any other constant acceleration.
     */
    Vector2 acceleration;

} Particle;


void initialize_particle(Particle *p, Vector2 start_position, Vector2 start_velocity, float radius);

void update_particle_position(Particle *p);

// draws particle that is stored in an array to windows
void draw_particle(Particle *p);

void check_collision_window(Particle *p, int wwin_width, int win_height);

int check_collision_particle(Particle *p1, Particle *p2);

void resolve_collision_particle(Particle *p1, Particle *p2);

#endif
