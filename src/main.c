#include <stdlib.h>
#include "raylib.h"
#include "particle.h"
#include "config.h"


int main(void) {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Simulation");

    SetTargetFPS(60);

    // Initialize Particle Array
    Particle particles[MAX_PARTICLES] = { 0 };
    for (int i = 0; i < MAX_PARTICLES; i++) {
        initialize_particle(&particles[i], 
                (Vector2){ GetRandomValue(0, WINDOW_WIDTH), GetRandomValue(0, WINDOW_HEIGHT) },
                (Vector2){ GetRandomValue(-50, 50) / 10.0f, GetRandomValue(-50, 50) / 10.0f },
                5.0f
                );
    }

    while (!WindowShouldClose()) {

        // Update Particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            update_particle_position(&particles[i]);
        }

        // Check for window collision
        for (int i = 0; i < MAX_PARTICLES; i++) {
            check_collision_window(&particles[i], WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Draw Particles
            for (int i = 0; i < MAX_PARTICLES; i++) {
                draw_particle(&particles[i]);
            }
        EndDrawing();
    }

    return 0;
}
