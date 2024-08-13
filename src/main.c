#include <stdlib.h>
#include "raylib.h"
#include "particle.h"


#define MAX_PARTICLES 1000


int main(void) {

    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Particle Simulation");

    SetTargetFPS(60);

    // Initialize Particle Array
    Particle particles[MAX_PARTICLES] = { 0 };
    for (int i = 0; i < MAX_PARTICLES; i++) {
        initialize_random_particle(&particles[i], 
                (Vector2){ GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight) },
                (Vector2){ GetRandomValue(-50, 50) / 10.0f, GetRandomValue(-50, 50) / 10.0f }
                );
    }


    while (!WindowShouldClose()) {

        //TODO: Update Particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            update_particle_position(&particles[i]);
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
