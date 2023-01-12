#ifndef OBJECT
#define OBJECT

#include "libGolabi.h"
#include "Vector2.h"
#include "ObjectType.h"

Struct(Object)
{
    // Physics
    Vector2 pos;
    Vector2 velocity;

    // Rendering
    ObjectType type;
};

#endif