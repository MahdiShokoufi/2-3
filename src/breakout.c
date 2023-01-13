#define MAIN

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>
#include "World.h"
#include "Player.h"
#include <math.h>
#include <stdlib.h>

typedef long long ll;

#define WIDTH 60
#define HEIGHT 30
#define FPS 45

wchar_t screen[HEIGHT][WIDTH];
ll st, t;

void draw()
{
    clear();

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            printw(" %lc", screen[i][j]);
        printw("\n");
    }
}

ll last;

World world;

void update(double deltatime)
{
    SimulateWorld(&world, deltatime);
}
void tick(char input)
{
    t = clock() - st;

    if (input == 'A' || input == 'a' || input == 4)
        HandleInput(&world.player, 'L');
    else if (input == 'D' || input == 'd' || input == 5)
        HandleInput(&world.player, 'R');
    else if (input == ' ')
    {
        Object *ball = InstantiateObject(&world, (Vector2){world.player.pos + GetPlayerLen(&world.player) / 2, HEIGHT - 2}, BALL);
        int dir;

        if (rand() % 2)
            dir = 45 + rand() % 20;
        else
            dir = 135 - rand() % 20;
        ball->velocity = mul(10, (Vector2){cos(dir), -sin(dir)});
    }

    if ((t - last) * FPS > CLOCKS_PER_SEC)
    {
        update(1.0 * (t - last) / CLOCKS_PER_SEC);
        last = t;
        RenderWorld(&world, screen);
        draw();
    }
}
int main()
{
    setlocale(LC_ALL, "");
    WINDOW *wind = initscr();
    keypad(wind, 1);
    nodelay(wind, 1);

    InitWorld(&world);

    while (1)
    {
        tick(getch());
    }
    return 0;
}
