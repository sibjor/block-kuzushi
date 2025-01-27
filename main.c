#include "raylib.h"
#include "raymath.h"

typedef struct Player {
    Vector2 position;
    float radius;
} Player;

int main() {
    InitWindow(800, 800, "Block-Kuzushi");
    SetTargetFPS(60);

    Player player = { {400, 750}, 20.0f };

    while (!WindowShouldClose()) {
        // Update player position
        if (IsKeyDown(KEY_RIGHT)) player.position.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) player.position.x -= 5.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(player.position, player.radius, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}