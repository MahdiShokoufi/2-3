#include "libGolabi.h"
#include "Object.h"
#include "Player.h"
#include "ObjectType.h"
#include <wchar.h>

#ifndef WORLD
#define WORLD

#define WIDTH 60
#define HEIGHT 30

Struct(World)
{
    Player player;
    Object **objects;
    int objn;
};

void SimulateWorld(World *world, double deltatime);
void RenderWorld(World *world, wchar_t (*screen)[WIDTH]);

#endif