#ifndef PLAYER
#define PLAYER

#include "libGolabi.h"
#include "PowerUp.h"

Struct(Player)
{
    int pos;
    int len;
    PowerUp decSpeed, incSpeed;
    PowerUp decBallSpeed, incBallSpeed;
    PowerUp decSize, incSize;
    PowerUp reverseInput;
};

int GetPlayerLen(Player *player);
void HandleInput(Player *player, char input);
#endif