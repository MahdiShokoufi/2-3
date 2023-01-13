#include "World.h"
#include "ObjectType.h"
#include "Vector2.h"
#include "ObjectType.h"
#include <stdlib.h>
#include "Utils.h"
#include <math.h>
#include "Vector2.h"
#include "assert.h"
void SimulateWorld(World *world, double deltatime)
{
    static int wgrid[WIDTH][HEIGHT];
    /// TODO
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            wgrid[i][j] = 0;
    for (Object *ptr = world->objects; ptr = ptr->nxt;)
    {
        if (ptr->type >= BRICK0)
            wgrid[(int)ptr->pos.x][(int)ptr->pos.y] = 1;
    }
    double gameSpeed = 5;

    for (Object *ptr = world->objects; ptr = ptr->nxt;)
    {
        if (ptr->type < BRICK0)
        {
            Vector2 futpos = add(ptr->pos, mul(deltatime * gameSpeed, ptr->velocity));
            if (ptr->type == BALL)
            {
                if (abs(ptr->velocity.x) >= abs(ptr->velocity.y)) // HORIZ
                {
                    int dir = ptr->velocity.x > 0 ? 1 : -1;
                    int x = ptr->pos.x + dir;
                    double y = ptr->pos.y;
                    for (;; x += dir, y += dir * ptr->velocity.y / ptr->velocity.x)
                    {
                        if (y < 1 || y >= HEIGHT)
                        {
                            x = maxd(0, x);
                            x = mind(WIDTH - 1, x);
                            y = maxd(1, y);
                            futpos = (Vector2){x, y};
                            ptr->velocity.y = -ptr->velocity.y;
                            break;
                        }
                        if (dir == 1 && x > futpos.x)
                            break;
                        if (dir == -1 && x < futpos.x)
                            break;
                        if (x < 0 || x >= WIDTH)
                        {
                            x = maxd(0, x);
                            x = mind(WIDTH - 1, x);
                            y = maxd(0, y);
                            futpos = (Vector2){x, y};
                            ptr->velocity.x = -ptr->velocity.x;
                            break;
                        }
                    }
                }
                else // VERT
                {
                    int dir = ptr->velocity.y > 0 ? 1 : -1;
                    int y = (int)ptr->pos.y + dir;
                    double x = ptr->pos.x;
                    for (;; y += dir, x += dir * ptr->velocity.x / ptr->velocity.y)
                    {
                        if (x < 1 || x > WIDTH - 2)
                        {
                            x = maxd(1, x);
                            x = mind(WIDTH - 2, x);
                            y = maxd(0, y);
                            futpos = (Vector2){x, y};
                            ptr->velocity.x = -ptr->velocity.x;
                            break;
                        }
                        if (dir == 1 && y > futpos.y)
                            break;
                        if (dir == -1 && y < futpos.y)
                            break;
                        if (y <= 0 || y >= HEIGHT)
                        {
                            x = maxd(0, x);
                            x = mind(WIDTH - 1, x);
                            y = maxd(0, y);
                            futpos = (Vector2){x, y};
                            ptr->velocity.y = -ptr->velocity.y;
                            break;
                        }
                    }
                }
            }
            ptr->pos = futpos;

            if (ptr->pos.y >= HEIGHT)
            {
                DestroyObject(world, ptr);
            }
        }
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
    for (Object *ptr = world->objects; ptr = ptr->nxt;)
    {
        int posx = ptr->pos.x;
        int posy = ptr->pos.y;
        screen[posy][posx] = ObjectIcons[ptr->type];
    }
    // Object *ptr = world->objects;
    // while (ptr->nxt)
    // {
    //     ptr = ptr->nxt;

    //     int posx = ptr->pos.x;
    //     int posy = ptr->pos.y;
    //     screen[posy][posx] = ObjectIcons[ptr->type];
    // }
}

Object *InstantiateObject(World *world, Vector2 pos, ObjectType type)
{
    Object *prv = world->lastobj;
    Object *obj = world->lastobj + 1;

    obj->pos = pos;
    obj->type = type;

    obj->nxt = NULL;
    obj->prv = prv;
    prv->nxt = obj;

    world->lastobj = obj;
    return obj;
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
    if (prv)
        prv->nxt = nxt;
    if (nxt)
        nxt->prv = prv;
    else
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
    static int wgrid[WIDTH][HEIGHT];
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            wgrid[i][j] = 0;

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
        if (!wgrid[posx][posy])
            InstantiateObject(world, (Vector2){posx, posy}, ty);
        wgrid[posx][posy] = 1;
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