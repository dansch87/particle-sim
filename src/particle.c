#include "particle.h"

void initialize_particle(Particle *p, Vector2 start_position, Vector2 start_velocity) {
    p->position = start_position;
    p->velocity = start_velocity;
}

void draw_particle(Particle *p) {
    float radius = 5.0;
    Color color = DARKBLUE;
    DrawCircle(p->position.x, p->position.y, radius, color); 
}

//TODO: window collosion
void update_particle_position(Particle *p) {
    p->position.x += p->velocity.x;
    p->position.y += p->velocity.y;
}
    
