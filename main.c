#include "raylib.h"
#include "raymath.h"

int main() {
    InitWindow(800, 800, "Block-Kuzushi");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}