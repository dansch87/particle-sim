#include <stdlib.h>
#include "raylib.h"
#include "particle.h"
#include "config.h"


/* TODO: Ocasionally, you can see an overlap of particles at the window borders. 
 * TODO: Add friction to simulate air friction that reducies kinetic energy.
 * TODO: Add UI panel to adjust variables, e.g. enabling and disabling friction.
 * TODO: Check particle collision has in worst case O(n^2). Optimize by using Quad Tree, etc.
 */



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
            check_collision_window(&particles[i], WINDOW_WIDTH, WINDOW_HEIGHT);
            for (int j = i + 1; j < MAX_PARTICLES; j++) {
                if (check_collision_particle(&particles[i], &particles[j])) {
                    resolve_collision_particle(&particles[i], &particles[j]);
                }
            }
        }

        // Check for window collision
        for (int i = 0; i < MAX_PARTICLES; i++) {
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
