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

enum CellType
{
    Empty = 0,
    Ball,
    PowerUp,
    PlusUp,
    Brick0,
    Brick1,
    BrickAdd,
    BrickUp
};

const wchar_t icons[] = {L' ', L'', L'', L'烙', L' ', L' ', L' ', L''};
void render()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            screen[i][j] = icons[rand() % 7];
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
    setlocale(LC_ALL, "");
    WINDOW *wind = initscr();
    nodelay(wind, 1);
    while (1)
    {
        tick(getch());
    }
    return 0;
}
