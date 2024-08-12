#include <stdlib.h>
#include "raylib.h"


int main(void) {

    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Particle Simulation");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    return 0;
}
