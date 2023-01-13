#include "Utils.h"
int maxi(int a, int b)
{
    return a > b ? a : b;
}
int maxd(double a, double b)
{
    return a > b ? a : b;
}

int mini(int a, int b)
{
    return a < b ? a : b;
}
int mind(double a, double b)
{
    return a < b ? a : b;
}

double lerp(double a, double b, double t)
{
    return a * (1 - t) + b * t;
}