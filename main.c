#include "raylib.h"
#include "raymath.h"

#define MAX_BLOCKS 100

typedef struct Player {
    int posX;
    int posY;
    int width;
    int height;
} Player;

typedef struct Ball {
    Vector2 position;
    float radius;
    Vector2 speed;
} Ball;

typedef struct Block {
    int posX;
    int posY;
    int width;
    int height;
    bool active;
    Color color;
} Block;

Block blocks[MAX_BLOCKS];

void BallBounce(Ball *ball, Player *player) {
    if (ball->position.x <= 0 || ball->position.x >= 800) {
        ball->speed.x *= -1;
    }
    if (ball->position.y <= 0 || ball->position.y >= 800) {
        ball->speed.y *= -1;
    }

    Rectangle playerRect = { player->posX, player->posY, player->width, player->height };
    Vector2 ballCenter = ball->position;

    if (CheckCollisionCircleRec(ballCenter, ball->radius, playerRect)) {
        ball->speed.y *= -1;
        ball->speed.x *= -1;
    }

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].active) {
            Rectangle blockRect = { blocks[i].posX, blocks[i].posY, blocks[i].width, blocks[i].height };
            if (CheckCollisionCircleRec(ballCenter, ball->radius, blockRect)) {
                ball->speed.y *= -1;
                blocks[i].active = false;
            }
        }
    }
}

void SpawnBricksAndBlocks() {
    int index = 0;
    Color colors[] = { RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE , BLACK};
    int colorCount = sizeof(colors) / sizeof(colors[0]);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            blocks[index] = (Block){ i * 80, j * 40, 70, 38, true, colors[index % colorCount] };
            index++;
        }
    }
}

int main() {
    InitWindow(800, 800, "Block-Kuzushi");
    SetTargetFPS(60);

    Player player = { 400, 750, 100, 20 };
    Ball ball = { { 160, 400 }, 16.0f, { 5.0f, 5.0f } };

    SpawnBricksAndBlocks();

    while (!WindowShouldClose()) {
        // Update player position
        if (IsKeyDown(KEY_RIGHT)) player.posX += 5.0f;
        if (IsKeyDown(KEY_LEFT)) player.posX -= 5.0f;

        // Update ball position
        ball.position = Vector2Add(ball.position, ball.speed);

        BallBounce(&ball, &player);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(player.posX, player.posY, player.width, player.height, BLACK);
        DrawCircleV(ball.position, ball.radius, BLACK);

        // Draw blocks
        for (int i = 0; i < MAX_BLOCKS; i++) {
            if (blocks[i].active) {
                DrawRectangle(blocks[i].posX, blocks[i].posY, blocks[i].width, blocks[i].height, blocks[i].color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
