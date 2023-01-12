#include "World.h"
#include "ObjectType.h"
#include "Vector2.h"
#include "ObjectType.h"
#include <stdlib.h>

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

    /// TODO

    // static int p = 0;
    // p++;
    // p %= WIDTH * HEIGHT;
    // screen[p / WIDTH][p % WIDTH] = ObjectIcons[5];

    // draw player
    for (int x = world->player.pos; x < GetPlayerLen(&world->player) + world->player.pos; x++)
        screen[HEIGHT - 1][x] = L'#';

    Object *ptr = world->objects;
    while (ptr->nxt)
    {
        ptr = ptr->nxt;

        int posx = ptr->pos.x;
        int posy = ptr->pos.y;
        screen[posy][posx] = ObjectIcons[ptr->type];
    }
    // for (size_t i = 0; i < world->objn; i++)
    // {
    //     screen[(int)world->objects[i]->pos.x][(int)world->objects[i]->pos.y] = ObjectIcons[world->objects[i]->type];
    // }
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

void DestroyObject(World *world, Object *obj)
{
    Object *nxt = obj->nxt;
    Object *prv = obj->prv;
    if (nxt)
        nxt->prv = prv;
    if (prv)
        prv->nxt = nxt;
}

void InitWorld(World *world)
{
    world->player.len = WIDTH / 10;
    world->player.pos = (WIDTH - world->player.len) / 2;
    world->objects = world->lastobj = New(Object, 100000);
    world->lastobj->prv = world->lastobj->nxt = NULL;

    for (int i = 0; i < 2; i++)
        InstantiateObject(world, (Vector2){1.0 * (rand() % WIDTH), 1.0 * (rand() % (HEIGHT - 1))}, BRICK1);
}