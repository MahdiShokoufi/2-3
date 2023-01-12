#include "World.h"
#include "ObjectType.h"
#include "Vector2.h"
#include "ObjectType.h"
#include <stdlib.h>

int wgrid[WIDTH][HEIGHT];
void SimulateWorld(World *world, double deltatime)
{
    for (size_t i = 0; i < world->objn; i++)
    {
        if (world->objects[i]->type != BALL)
        {
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

    // static int p = 0;
    // p++;
    // p %= WIDTH * HEIGHT;
    // screen[p / WIDTH][p % WIDTH] = ObjectIcons[5];

    // draw player
    for (int x = world->player.pos; x < GetPlayerLen(&world->player) + world->player.pos; x++)
        screen[HEIGHT - 1][x] = L'#';
    // for (size_t i = 0; i < world->objn; i++)
    // {
    //     screen[(int)world->objects[i]->pos.x][(int)world->objects[i]->pos.y] = ObjectIcons[world->objects[i]->type];
    // }
}

void InstantiateObject(World *world, Vector2 pos, ObjectType type)
{
}

void InitWorld(World *world)
{
    world->player.len = WIDTH / 10;
    world->player.pos = (WIDTH - world->player.len) / 2;
}