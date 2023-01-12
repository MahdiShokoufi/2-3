#ifndef WORLD
#define WORLD

#include "libGolabi.h"
#include "Object.h"
#include "Player.h"
#include <wchar.h>

#define WIDTH 60
#define HEIGHT 30

Struct(World)
{
    Player player;
    Object *objects;
    Object *lastobj;
};

void SimulateWorld(World *world, double deltatime);
void RenderWorld(World *world, wchar_t (*screen)[WIDTH]);
void InstantiateObject(World *world, Vector2 pos, ObjectType type);
void InitWorld(World *world);

#endif