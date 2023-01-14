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
    // World State
    Player player;
    Object *objects;
    Object *lastobj;
    int turnId;
    int isStarted;

    // Score State
    /// TODO
};

void SimulateWorld(World *world, double deltatime);
void RenderWorld(World *world, wchar_t (*screen)[WIDTH]);
Object *InstantiateObject(World *world, Vector2 pos, ObjectType type);
void OnObjectDestroyed(World *World, Object *obj);
void DestroyObject(World *world, Object *obj);
void ForceDestroyObject(World *world, Object *obj);
void InitWorld(World *world);
void GenerateMap(World *world);
void ReGenerateMap(World *world);
void ShootBall(World *world);

#endif