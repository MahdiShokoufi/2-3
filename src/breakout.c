#define MAIN

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>
#include "World.h"
#include "Player.h"

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

    if (input == 'A' || input == 'a' || input == 4)
        HandleInput(&world.player, 'L');
    else if (input == 'D' || input == 'd' || input == 5)
        HandleInput(&world.player, 'R');

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

    world.player.len = WIDTH / 10;
    world.player.pos = (WIDTH - world.player.len) / 2;

    while (1)
    {
        tick(getch());
    }
    return 0;
}
