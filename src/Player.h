#include "libGolabi.h"
#include "PowerUp.h"

#ifndef PLAYER
#define PLAYER

Struct(Player)
{
    double pos;
    PowerUp decSpeed, incSpeed;
    PowerUp decBallSpeed, incBallSpeed;
    PowerUp decSize, incSize;
    PowerUp reverseInput;
};

#endif