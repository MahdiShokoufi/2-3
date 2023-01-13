#ifndef VECTOR2
#define VECTOR2

#include "libGolabi.h"

Struct(Vector2)
{
    double x, y;
};

Vector2 add(Vector2 a, Vector2 b);
Vector2 sub(Vector2 a, Vector2 b);
Vector2 mul(double a, Vector2 b);
double cross(Vector2 a, Vector2 b);
double dot(Vector2 a, Vector2 b);

Vector2 Lerp(Vector2 a, Vector2 b, double t);

#endif