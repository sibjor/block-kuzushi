#include "game.h"
#include "shapes.h"
#include "player.h"
#include <raylib.h>

void InitGame(int width, int height, const char *title) {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    Player player;
    InitPlayer(&player, "Player1", 0, 100, 5, 10);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("It works!", 20, 20, 20, BLACK);
        DrawLineCustom(100, 100, 200, 200, RED);
        DrawSquareCustom(300, 300, 50, BLUE);
        DrawRectangleCustom(400, 300, 100, 50, BLUE);
        DrawCircleCustom(500, 400, 30, GREEN);
        DrawCircleCustom(player.position.x, player.position.y, 10, RED);
        EndDrawing();
    }

    CloseWindow();
}