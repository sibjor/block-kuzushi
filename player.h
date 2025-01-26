#ifndef PLAYER_H
#define PLAYER_H

#include "functions.h"

typedef struct {
    char name[50];
    int score;
    int health;
    int speed;
    int weaponSpeed;
    Position position;
} Player;

void InitPlayer(Player *player, const char *name, int score, int health, int speed, int weaponSpeed);

#endif // PLAYER_H