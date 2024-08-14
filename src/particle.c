#include "particle.h"

void initialize_particle(Particle *p, Vector2 start_position, Vector2 start_velocity, float radius) {
    p->position = start_position;
    p->velocity = start_velocity;
    p->radius = radius;
}

void draw_particle(Particle *p) {
    Color color = DARKBLUE;
    DrawCircle(p->position.x, p->position.y, p->radius, color); 
}

void update_particle_position(Particle *p) {
    p->position.x += p->velocity.x;
    p->position.y += p->velocity.y;
}

void check_collision_window(Particle *p, int win_width, int win_height) {

    // Change velocity direction when collision with window border occurs
    if (p->position.x <= 0 || p->position.x >= win_width) {
        p->velocity.x *= -1;
    }
    if (p->position.y <= 0 || p->position.y >= win_height) {
        p->velocity.y *= -1;
    }

    // Correction of position if particle has cross the window border
    if (p->position.x < 0) {
        p->position.x = 0 + p->radius;
    }
    if (p->position.x > win_width) {
        p->position.x = win_width - p->radius;
    }
    if (p->position.y < 0) {
        p->position.y = 0 + p->radius;
    }
    if (p->position.y > win_height) {
        p->position.y = win_height - p->radius;
    }
}
