#include "World.h"
#include "ObjectType.h"
#include "Vector2.h"
#include "ObjectType.h"
#include <stdlib.h>
#include "Utils.h"
#include <math.h>
#include "Vector2.h"
#include "assert.h"
#include "stdio.h"

FILE *dbg;

void OnBallHit(World *world, Object *block)
{
    // assert(0);
    DestroyObject(world, block);
}
int ValidX(int x)
{
    fprintf(dbg, "check x:%d\n", x);
    return x >= 0 && x < WIDTH;
}
int ValidY(int y)
{
    fprintf(dbg, "check y:%d\n", y);
    return y >= 0 && y < HEIGHT;
}
Object *Travel(Object *obj, Vector2 dst, Object *wgrid[WIDTH][HEIGHT])
{
    while (1)
    {

        // fprintf(file, "%lf,%lf -> %lf,%lf\n", obj->pos.x, obj->pos.y, dst.x, dst.y);
        if ((int)obj->pos.x == (int)dst.x && (int)obj->pos.y == (int)dst.y)
        {
            obj->pos = dst;
            return NULL;
        }

        Vector2 delta = sub(dst, obj->pos);

        double dx = 0;
        if ((int)obj->pos.x < (int)dst.x)
            dx = fmax((int)(obj->pos.x + 1) - obj->pos.x, 0.001);
        else if ((int)obj->pos.x > (int)dst.x)
            dx = fmin(((int)obj->pos.x) - obj->pos.x, -0.001);
        double dxy = dx / delta.x * delta.y;

        double dy = 0;
        if ((int)obj->pos.y < (int)dst.y)
            dy = fmax((int)(obj->pos.y + 1) - obj->pos.y, 0.001);
        else if ((int)obj->pos.y > (int)dst.y)
            dy = fmin(((int)obj->pos.y) - obj->pos.y, -0.001);
        double dyx = dy / delta.y * delta.x;

        // fprintf(file, "%lf,%lf => %lf,%lf == %lf,%lf , %lf,%lf   ", obj->pos.x, obj->pos.y, dst.x, dst.y, dx, dxy, dyx, dy);
        // fflush(file);

        if ((int)obj->pos.x == (int)dst.x || ((int)obj->pos.y != (int)dst.y && fabs(dyx) <= fabs(dx)))
        {
            // assert(0);

            if (ValidX((int)obj->pos.x) && ValidY((int)obj->pos.y + (dy > 0 ? 1 : -1)) && wgrid[(int)obj->pos.x][(int)obj->pos.y + (dy > 0 ? 1 : -1)])
            {
                obj->velocity.y = -obj->velocity.y;
                return wgrid[(int)obj->pos.x][(int)obj->pos.y + (dy > 0 ? 1 : -1)];
            }

            obj->pos.y += dy * 1.001;
            obj->pos.x += dyx * 1.001;

            int cng = 0;
            if (obj->pos.y <= 0)
            {
                obj->velocity.y = -obj->velocity.y;
                cng = 1;
            }
            if (obj->pos.x <= 0 || obj->pos.x >= WIDTH - 1)
            {
                obj->velocity.x = -obj->velocity.x;
                cng = 1;
            }
            if (cng || obj->pos.y >= HEIGHT - 1)
                return NULL;
        }
        else
        {
            // assert(0);

            if (ValidX((int)obj->pos.x + (dx > 0 ? 1 : -1)) && ValidY((int)obj->pos.y) && wgrid[(int)obj->pos.x + (dx > 0 ? 1 : -1)][(int)obj->pos.y])
            {
                obj->velocity.x = -obj->velocity.x;
                return wgrid[(int)obj->pos.x + (dx > 0 ? 1 : -1)][(int)obj->pos.y];
            }

            obj->pos.y += dxy * 1.001;
            obj->pos.x += dx * 1.001;

            int cng = 0;
            if (obj->pos.y <= 0)
            {
                obj->velocity.y = -obj->velocity.y;
                cng = 1;
            }
            if (obj->pos.x <= 0 || obj->pos.x >= WIDTH - 1)
            {
                obj->velocity.x = -obj->velocity.x;
                cng = 1;
            }
            if (cng || obj->pos.y >= HEIGHT - 1)
                return NULL;
        }
    }
    return NULL;
}

void SimulateWorld(World *world, double deltatime)
{
    dbg = fopen("log.txt", "a");

    static Object *wgrid[WIDTH][HEIGHT];

    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            wgrid[i][j] = NULL;

    // player

    for (int x = world->player.pos; x < GetPlayerLen(&world->player) + world->player.pos; x++)
        wgrid[x][HEIGHT - 1] = 1;

    // world
    for (Object *ptr = world->objects; ptr = ptr->nxt;)
    {
        if (ptr->type >= BRICK0)
            wgrid[(int)ptr->pos.x][(int)ptr->pos.y] = ptr;
    }
    double gameSpeed = 1;

    for (Object *ptr = world->objects; ptr = ptr->nxt;)
    {
        if (ptr->type < BRICK0)
        {
            Vector2 futpos = add(ptr->pos, mul(deltatime * gameSpeed, ptr->velocity));
            if (ptr->type == BALL)
            {
                Object *wall = Travel(ptr, futpos, wgrid);
                if (wall > 1)
                    OnBallHit(world, wall);
            }
            else
            {
                ptr->pos = futpos;
            }

            if (ptr->pos.y >= HEIGHT - 1)
            {
                DestroyObject(world, ptr);
            }
        }
    }
    fclose(dbg);
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

    obj->exist = 1;
    obj->nxt = NULL;
    obj->prv = prv;
    prv->nxt = obj;

    world->lastobj = obj;
    return obj;
}

void ForceDestroyObject(World *world, Object *obj)
{
    if (!obj)
        return;
    if (!obj->exist)
        return;

    Object *nxt = obj->nxt;
    Object *prv = obj->prv;
    if (prv)
        prv->nxt = nxt;
    if (nxt)
        nxt->prv = prv;
    else
        world->lastobj = prv;
    obj->exist = 0;
}
void OnObjectDestroyed(World *World, Object *obj)
{
    /// TODO
}

void DestroyObject(World *world, Object *obj)
{
    if (!obj)
        return;
    if (!(obj->exist))
        return;

    OnObjectDestroyed(world, obj);

    Object *nxt = obj->nxt;
    Object *prv = obj->prv;
    if (prv)
        prv->nxt = nxt;
    if (nxt)
        nxt->prv = prv;
    else
        world->lastobj = prv;
    obj->exist = 0;
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