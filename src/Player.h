#include "libGolabi.h"
#include "PowerUp.h"

#ifndef PLAYER
#define PLAYER

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

#endif