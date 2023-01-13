#include "World.h"
#include "ObjectType.h"
#include "Vector2.h"
#include "ObjectType.h"
#include <stdlib.h>
#include "Utils.h"
#include <math.h>

int wgrid[WIDTH][HEIGHT];
void SimulateWorld(World *world, double deltatime)
{
    /// TODO
    Object *ptr = world->objects;
    while (ptr->nxt)
    {
        ptr = ptr->nxt;
    }
}

void RenderWorld(World *world, wchar_t (*screen)[WIDTH])
{
    // BackGround
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            screen[i][j] = ObjectIcons[0];
        }
    }

    // Player
    for (int x = world->player.pos; x < GetPlayerLen(&world->player) + world->player.pos; x++)
        screen[HEIGHT - 1][x] = L'#';

    // Blocks
    Object *ptr = world->objects;
    while (ptr->nxt)
    {
        ptr = ptr->nxt;

        int posx = ptr->pos.x;
        int posy = ptr->pos.y;
        screen[posy][posx] = ObjectIcons[ptr->type];
    }
}

void InstantiateObject(World *world, Vector2 pos, ObjectType type)
{
    Object *prv = world->lastobj;
    Object *obj = world->lastobj + 1;

    obj->pos = pos;
    obj->type = type;

    obj->nxt = NULL;
    obj->prv = prv;
    prv->nxt = obj;

    world->lastobj = obj;
}

void ForceDestroyObject(World *world, Object *obj)
{
    Object *nxt = obj->nxt;
    Object *prv = obj->prv;
    if (nxt)
        nxt->prv = prv;
    if (prv)
        prv->nxt = nxt;
    world->lastobj = prv;
}
void OnObjectDestroyed(World *World, Object *obj)
{
    /// TODO
}

void DestroyObject(World *world, Object *obj)
{
    Object *nxt = obj->nxt;
    Object *prv = obj->prv;
    if (nxt)
        nxt->prv = prv;
    if (prv)
        prv->nxt = nxt;
    world->lastobj = prv;

    OnObjectDestroyed(world, obj);
}

void InitWorld(World *world)
{
    world->player.len = WIDTH / 10;
    world->player.pos = (WIDTH - world->player.len) / 2;
    world->objects = world->lastobj = New(Object, 100000);
    world->lastobj->prv = world->lastobj->nxt = NULL;

    GenerateMap(world);
}

void GenerateMap(World *world)
{
    int grid[WIDTH][HEIGHT];
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            grid[i][j] = 0;

    int maxy = lerp(HEIGHT / 3, HEIGHT * 4 / 5, 1.0 - sqrt(exp(-world->turnId)));
    int maxd = lerp(WIDTH / 3, WIDTH * 2 / 3, 1.0 - sqrt(exp(-world->turnId)));
    world->turnId++;

    for (int i = 0; i < maxy * maxd; i++)
    {
        int posx = rand() % WIDTH, posy = rand() % maxy, ty = rand() % 100;
        // WRand
        for (int i = 0; i <= ObjectTypeCnt; i++)
        {
            ty -= ObjectProb[i];
            if (ty <= 0)
            {
                ty = i;
                break;
            }
        }
        if (!grid[posx][posy])
            InstantiateObject(world, (Vector2){posx, posy}, ty);
        grid[posx][posy] = 1;
    }
}

void ReGenerateMap(World *world)
{
    while (world->lastobj != world->objects)
    {
        ForceDestroyObject(world, world->lastobj);
    }
    GenerateMap(world);
}