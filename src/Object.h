#include "libGolabi.h"
#include "Vector2.h"
#include "SpriteType.h"

#ifndef OBJECT
#define OBJECT

Struct(Object)
{
    // Physics
    Vector2 pos;
    Vector2 velocity;

    // Rendering
    SpriteType sprite;
};

#endif