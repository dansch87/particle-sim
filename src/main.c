#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"
#include "config.h"
#include "particle.h"
#include "quadtree.h"
#include "arena.h"

/* TODO: Ocasionally, you can see an overlap of particles at the window borders. 
 * TODO: Add friction to simulate air friction that reducies kinetic energy.
 * TODO: Add UI panel to adjust variables, e.g. enabling and disabling friction.
 * TODO: Check particle collision has in worst case O(n^2). Optimize by using Quad Tree, etc.
 */


int main(void) {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Simulation");

    SetTargetFPS(60);

    // Create Particle Texture
    Texture2D particleTexture = particle_create_texture(PARTICLE_RADIUS, PARTICLE_COLOR);

    // Initialize Particle Array
    Particle particles[MAX_PARTICLES] = { 0 };
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particle_init(&particles[i], 
                (Vector2){ GetRandomValue(0, WINDOW_WIDTH), GetRandomValue(0, WINDOW_HEIGHT) },
                //(Vector2){ GetRandomValue(0, 250), GetRandomValue(0, 250) },
                (Vector2){(float)GetRandomValue(-PARTICLE_VELOCITY, PARTICLE_VELOCITY), (float)GetRandomValue(-PARTICLE_VELOCITY, PARTICLE_VELOCITY)},
                PARTICLE_RADIUS
                );
    }

    // Create Arena
    Arena arena = arena_init(MB * 10);

    Rectangle boundary = (Rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	QuadTree *quadtree = quadtree_create(&arena, &boundary);


    while (!WindowShouldClose()) {

        float delta_time = GetFrameTime();

        //quadtree_clear(quadtree);
        arena_clear(&arena);
        QuadTree *quadtree = quadtree_create(&arena, &boundary);
        
        
		for (int i = 0; i < MAX_PARTICLES; i++) {
            quadtree_insert(&arena, quadtree, &particles[i]);
        }
        printf("Quadtree Element Count %d\n", quadtree_element_count(quadtree));
        arena_print(&arena);

        // Update Particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            particle_update_position(&particles[i], delta_time);
            particle_handle_window_collision(&particles[i]);

            Particle* nearbyParticles[MAX_NEARBY_PARTICLES];
                int count = 0;
                Rectangle searchRange = {
                    particles[i].position.x - SEARCH_RADIUS,
                    particles[i].position.y - SEARCH_RADIUS,
                    SEARCH_RADIUS,
                    SEARCH_RADIUS
                };

                quadtree_query(quadtree, searchRange, nearbyParticles, &count, MAX_NEARBY_PARTICLES);
                for (int j = 0; j < count; j++) {
                    
                    if (&particles[i] != nearbyParticles[j]) {
                        Rectangle particleB = {
                            nearbyParticles[j]->position.x - nearbyParticles[j]->radius,
                            nearbyParticles[j]->position.y - nearbyParticles[j]->radius,
                            SEARCH_RADIUS,
                            SEARCH_RADIUS
                        };
                        
                        if (CheckCollisionRecs(searchRange, particleB)) {
                            particle_resolve_particle_collision(&particles[i], nearbyParticles[j]);
                        }
                    }
			    }
		    }


        // Update Particles
        /*
        for (int i = 0; i < MAX_PARTICLES; i++) {
            particle_update_position(&particles[i], delta_time);
            particle_handle_window_collision(&particles[i]);
            for (int j = i + 1; j < MAX_PARTICLES; j++) {
                if (particle_check_particle_collision(&particles[i], &particles[j])) {
                    particle_resolve_particle_collision(&particles[i], &particles[j]);
                }
            }
        }
        */

        
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);
            DrawFPS(10, 10);

            // Draw Particles
            for (int i = 0; i < MAX_PARTICLES; i++) {
                particle_draw_texture(&particleTexture, &particles[i]);
                //particle_draw(&particles[i]);
            }

            quadtree_draw(quadtree);

        EndDrawing();
    }

    return 0;
}
