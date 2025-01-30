/*
Author: Sixten Björling
Course: C Programming in Raylib
Teacher: Sebastian Jensen
Assignment: Block-Kuzushi
Date: 2025-01-31
Notes: CMakeLists.txt will fetch Raylib
*/

#include "raylib.h"
#include "raymath.h"

#define MAX_BLOCKS 100
#define GAME_OVER_TEXT "Game Over! Press R to Restart"
#define GAME_OVER_TEXT_X 200
#define GAME_OVER_TEXT_Y 400
#define GAME_OVER_TEXT_SIZE 20

#define GAME_WIN_TEXT "You Win! Press R to Restart"
#define GAME_WIN_TEXT_X 200
#define GAME_WIN_TEXT_Y 400
#define GAME_WIN_TEXT_SIZE 20

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

int lives = 3;

void BallBounce(Ball *ball, Player *player) {
  if (ball->position.x <= 0 || ball->position.x >= 800) {
    ball->speed.x *= -1;
  }
  if (ball->position.y <= 0) {
    ball->speed.y *= -1;
  }
  if (ball->position.y >= 800) {
    lives--;
    ball->position = (Vector2){400, 400};
    ball->speed = (Vector2){5.0f, 5.0f};
  }

  Rectangle playerRect = {player->posX, player->posY, player->width,
                          player->height};
  Vector2 ballCenter = ball->position;

  if (CheckCollisionCircleRec(ballCenter, ball->radius, playerRect)) {
    ball->speed.y *= -1;
    float relativeIntersectX =
        (ballCenter.x - (player->posX + player->width / 2)) /
        (player->width / 2); // equivalent to (*player).width...
    ball->speed.x = relativeIntersectX *
                    5.0f; // This part is a bit tricky, it changes the ball's
                          // direction based on where it hits the player
  }

  for (int i = 0; i < MAX_BLOCKS; i++) {
    if (blocks[i].active) {
      Rectangle blockRect = {blocks[i].posX, blocks[i].posY, blocks[i].width,
                             blocks[i].height};
      if (CheckCollisionCircleRec(ballCenter, ball->radius, blockRect)) {
        if (blocks[i].color.r == RED.r && blocks[i].color.g == RED.g &&
            blocks[i].color.b == RED.b && blocks[i].color.a == RED.a) {
          lives++; // Add lives to player hitting a red block
          blocks[i].active = false;
        } else if (blocks[i].color.r == BLACK.r &&
                   blocks[i].color.g == BLACK.g &&
                   blocks[i].color.b == BLACK.b &&
                   blocks[i].color.a == BLACK.a) {
          ball->speed.y *= -1; // Hitting a brick with (black) colour
        } else {
          blocks[i].active = false;
          float overlapX =
              ballCenter.x - (blocks[i].posX + blocks[i].width / 2);
          float overlapY =
              ballCenter.y - (blocks[i].posY + blocks[i].height / 2);
          if (fabs(overlapX) > fabs(overlapY)) {
            ball->speed.x *= -1;
          } else {
            ball->speed.y *= -1;
          }
        }
      }
    }
  }
}

void SpawnBricksAndBlocks() {
  int index = 0;
  Color colors[] = {RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE, BLACK};
  int colorCount = sizeof(colors) / sizeof(colors[0]);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      blocks[index] =
          (Block){i * 80, j * 40, 70, 38, true, colors[index % colorCount]};
      index++;
    }
  }
}

void GameOver(int *lives, Vector2 *ballPosition, Vector2 *ballSpeed) {
  DrawText(GAME_OVER_TEXT, GAME_OVER_TEXT_X, GAME_OVER_TEXT_Y,
           GAME_OVER_TEXT_SIZE, RED);
  if (IsKeyPressed(KEY_R)) {
    *lives = 3;
    *ballPosition = (Vector2){400, 400};
    *ballSpeed = (Vector2){5.0f, 5.0f};
    SpawnBricksAndBlocks();
  }
}

void GameWin(int *lives, Vector2 *ballPosition, Vector2 *ballSpeed) {
  DrawText(GAME_WIN_TEXT, GAME_WIN_TEXT_X, GAME_WIN_TEXT_Y, GAME_WIN_TEXT_SIZE,
           GREEN);
  if (IsKeyPressed(KEY_R)) {
    *lives = 3;
    *ballPosition = (Vector2){400, 400};
    *ballSpeed = (Vector2){5.0f, 5.0f};
    SpawnBricksAndBlocks();
  }
}

int main() {
  InitWindow(800, 800, "Block-Kuzushi");
  SetTargetFPS(60);

  Player player = {400, 750, 100, 20};
  Ball ball = {{400, 400}, 16.0f, {5.0f, 5.0f}};

  SpawnBricksAndBlocks();

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT) && player.posX + player.width < 800)
      player.posX += 5.0f;
    if (IsKeyDown(KEY_LEFT) && player.posX > 0)
      player.posX -= 5.0f;

    if (lives > 0) {
      ball.position = Vector2Add(ball.position, ball.speed);
      BallBounce(&ball, &player);
    }

    bool allBlocksInactive = true;
    for (int i = 0; i < MAX_BLOCKS; i++) {
      if (blocks[i].active) {
        allBlocksInactive = false;
        break;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(player.posX, player.posY, player.width, player.height, BLACK);
    DrawCircleV(ball.position, ball.radius, BLACK);

    for (int i = 0; i < MAX_BLOCKS; i++) {
      if (blocks[i].active) {
        DrawRectangle(blocks[i].posX, blocks[i].posY, blocks[i].width,
                      blocks[i].height, blocks[i].color);
      }
    }

    DrawText(TextFormat("Lives: %d", lives), 10, 10, 20, DARKGRAY);

    if (lives <= 0) {
      GameOver(&lives, &ball.position, &ball.speed);
    } else if (allBlocksInactive || IsKeyPressed(KEY_T)) {
      GameWin(&lives, &ball.position, &ball.speed);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}