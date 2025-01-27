#include "raylib.h"
#include "raymath.h"

typedef struct Player {
    int posX;
    int posY;
    int width;
    int height;
} Player;
typedef struct Ball{
  int posX;
  int posY;
  float radius;
  float speedX;
  float speedY;
}Ball;

void BallBounce(Ball *ball, Player *player) {
    if (ball->posX <= 0 || ball->posX >= 800) {
        ball->speedX *= -1;
    }
    if (ball->posY <= 0 || ball->posY >= 800) {
        ball->speedY *= -1;
    }

    Rectangle playerRect = { player->posX, player->posY, player->width, player->height };
    Vector2 ballCenter = { ball->posX, ball->posY };

    if (CheckCollisionCircleRec(ballCenter, ball->radius, playerRect)) {
        ball->speedY *= -1;
        ball->speedX *= -1;
    }
}

int main() {
    InitWindow(800, 800, "Block-Kuzushi");
    SetTargetFPS(60);

    Player player = { 400, 750, 100, 20};
    Ball ball = {160, 400, 16.0f, 5.0f, 5.0f};

    while (!WindowShouldClose()) {
        // Update player position
        if (IsKeyDown(KEY_RIGHT)) player.posX += 5.0f;
        if (IsKeyDown(KEY_LEFT)) player.posX -= 5.0f;
        // Update ball position
        ball.posX += ball.speedX;
        ball.posY += ball.speedY;
        BallBounce(&ball, &player);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(player.posX, player.posY,player.width, player.height, BLACK);
        DrawCircle(ball.posX, ball.posY, ball.radius, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
