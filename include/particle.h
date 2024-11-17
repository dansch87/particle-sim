#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "raylib.h"


typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    float radius;
} Particle;

Texture2D particle_create_texture(float radius, Color color);

void particle_draw_texture(Texture2D *t, Particle *p);

void particle_init(Particle *p, Vector2 start_position, Vector2 start_velocity, float radius);

void particle_update_position(Particle *p, float delta_time);

void particle_draw(Particle *p);

void particle_handle_window_collision(Particle *p);

int particle_check_particle_collision(Particle *p1, Particle *p2);

void particle_resolve_particle_collision(Particle *p1, Particle *p2);

#endif
