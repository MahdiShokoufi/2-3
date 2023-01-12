#include "libGolabi.h"
#include "Object.h"
#include "Player.h"

#ifndef WORLD
#define WORLD

Struct(World)
{
    Player player;
    Object *objects;
};

#endif