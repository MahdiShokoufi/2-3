#ifndef POWERUP
#define POWERUP

#include "libGolabi.h"

Struct(PowerUp)
{
    double endtime;
};

int isActive(PowerUp p, double ttime);

#endif