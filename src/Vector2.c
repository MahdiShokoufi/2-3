#include "Vector2.h"
#include "Utils.h"

Vector2 add(Vector2 a, Vector2 b)
{
    Vector2 res = {a.x + b.x, a.y + b.y};
    return res;
}
Vector2 sub(Vector2 a, Vector2 b)
{
    Vector2 res = {a.x - b.x, a.y - b.y};
    return res;
}
Vector2 mul(double a, Vector2 b)
{
    Vector2 res = {a * b.x, a * b.y};
    return res;
}
double cross(Vector2 a, Vector2 b)
{
    return a.x * b.y - a.y * b.x;
}
double dot(Vector2 a, Vector2 b)
{
    return a.x * b.x + a.y * b.y;
}

Vector2 Lerp(Vector2 a, Vector2 b, double t)
{
    return (Vector2){lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}