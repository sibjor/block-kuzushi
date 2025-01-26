#include "player.h"
#include <string.h>

void InitPlayer(Player *player, const char *name, int score, int health, int speed, int weaponSpeed)
{
    strncpy(player->name, name, sizeof(player->name) - 1);
    player->name[sizeof(player->name) - 1] = '\0';
    player->score = score;
    player->health = health;
    player->speed = speed;
    player->weaponSpeed = weaponSpeed;
    SetPosition(&player->position, 100, 100);
}