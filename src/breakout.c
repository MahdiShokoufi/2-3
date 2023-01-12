#define MAIN

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>
#include "World.h"

typedef long long ll;

#define WIDTH 60
#define HEIGHT 30
#define FPS 20

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
}
void tick(char input)
{
    t = clock() - st;

    if (input == 'A' || input == 'a')
        world.player.pos--;
    else if (input == 'D' || input == 'd')
        world.player.pos++;

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
    nodelay(wind, 1);

    world.player.len = WIDTH / 10;
    world.player.pos = (WIDTH - world.player.len) / 2;

    while (1)
    {
        tick(getch());
    }
    return 0;
}
