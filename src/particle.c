#include <math.h>
#include <stdio.h>
#include "particle.h"
#include "raylib.h"
#include "raymath.h"

void initialize_particle(Particle *p, Vector2 start_position, Vector2 start_velocity, float radius) {
    p->position = start_position;
    p->velocity = start_velocity;
    p->radius = radius;
}

void draw_particle(Particle *p) {
    Color color = YELLOW;
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
    if (p->position.x <= 0) {
        p->position.x = 0 + p->radius;
    }
    if (p->position.x >= win_width) {
        p->position.x = win_width - p->radius;
    }
    if (p->position.y <= 0) {
        p->position.y = 0 + p->radius;
    }
    if (p->position.y >= win_height) {
        p->position.y = win_height - p->radius;
    }
}

static float vector_magnitude(Vector2 *pos1, Vector2 *pos2) {
    float dist_x = pos2->x - pos1->x;
    float dist_y = pos2->y - pos1->y;
    return sqrtf(dist_x * dist_x + dist_y * dist_y);
}

int check_collision_particle(Particle *p1, Particle *p2) {
    float magnitude = vector_magnitude(&p1->position, &p2->position);
    // Check if distance between particles is < sum of radius of both particles
    return magnitude <= (p1->radius + p2->radius);
}

void resolve_collision_particle(Particle *p1, Particle *p2) {
    // Step 1: Check if particles are approaching each other and handling the collision is necessary.
    // Step 1.1: Calculate Unit Normal Vector
    Vector2 normal = { p2->position.x - p1->position.x, p2->position.y - p1->position.y };
    // Normalize normal Vector to get its unit vector
    float distance = Vector2Length(normal);
    normal.x /= distance;
    normal.y /= distance;

    // Step 1.2: Caluculate Velocity for Unit Normal Vector
    Vector2 relative_velocity = { p2->velocity.x - p1->velocity.x, p2->velocity.y - p1->velocity.y };
    float velocity_along_normal = relative_velocity.x * normal.x + relative_velocity.y * normal.y;
    // Step 1.3: Check direction for collision
    // velocity < 0: particles approaching each other
    // velocity > 0: particles are moving away from each other
    if (velocity_along_normal > 0) return;

    // Step 2: Update velocity based on elastic colllision formulas
    float restitution = 1.0f;
    float impulse = (-(1 + restitution) * velocity_along_normal) / 2;
    Vector2 impulse_vector = { impulse * normal.x, impulse * normal.y };
    p1->velocity.x -= impulse_vector.x;
    p1->velocity.y -= impulse_vector.y;
    p2->velocity.x += impulse_vector.x;
    p2->velocity.y += impulse_vector.y;
}
