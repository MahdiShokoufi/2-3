#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <math.h>

void test()
{
    static int x = 0;
    x++;
    printf("%lf", 1 - sqrt(exp(-x)));
}

int main()
{
}
