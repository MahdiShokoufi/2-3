#include <ncurses.h>
#include <locale.h>
#include <wchar.h>

#include <time.h>

typedef long long ll;

#define WIDTH 60
#define HEIGHT 30
#define FPS 15

wchar_t screen[WIDTH][HEIGHT];
ll st, t;

struct Vector2
{
    double x, y;
};

struct Vector2 add(struct Vector2 a, struct Vector2 b)
{
    struct Vector2 res = {a.x + b.x, a.y + b.y};
    return res;
}
struct Vector2 sub(struct Vector2 a, struct Vector2 b)
{
    struct Vector2 res = {a.x - b.x, a.y - b.y};
    return res;
}
struct Vector2 mul(double a, struct Vector2 b)
{
    struct Vector2 res = {a * b.x, a * b.y};
    return res;
}
double cross(struct Vector2 a, struct Vector2 b)
{
    return a.x * b.y - a.y * b.x;
}
double dot(struct Vector2 a, struct Vector2 b)
{
    return a.x * b.x + a.y * b.y;
}

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
void render()
{
    const wchar_t ball = L'';
    const wchar_t empty = L' ';
    const wchar_t brick1 = L'';
    const wchar_t brick2 = L'';
    const wchar_t brickadd = L'';
    const wchar_t brickup = L'';

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            screen[i][j] = brick2;
        }
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
        render();
        draw();
    }
}
int main()
{
    WINDOW *wind = initscr();
    nodelay(wind, 1);
    setlocale(LC_ALL, "");
    while (1)
    {
        tick(getch());
    }
    return 0;
}
