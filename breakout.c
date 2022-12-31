#include <ncurses.h>
// #include <stdio.h>
#include <time.h>

typedef long long ll;
#define WIDTH 30
#define HEIGHT 50
#define FPS 15

char screen[WIDTH][HEIGHT];
ll st, t;

struct Vector2
{
    double x, y;
};

void draw()
{
    clear();

    for (int i = 0; i < WIDTH - t; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
            printw(" %c ", screen[i + t / 1000][j]);
        printw("\n");
    }
}
ll last;

void update(double deltatime)
{
}
void tick(char input)
{
    t = clock() - st;

    if ((t - last) * FPS > CLOCKS_PER_SEC)
    {
        update(1.0 * (t - last) / CLOCKS_PER_SEC);
        last = t;
        draw();
    }
}
int main()
{
    WINDOW *wind = initscr();
    nodelay(wind, 1);
    while (1)
    {
        tick(getch());
    }
    return 0;
}