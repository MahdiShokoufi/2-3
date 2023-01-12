#include "libGolabi.h"
#include "Vector2.h"
#include "ObjectType.h"
#include <wchar.h>

#ifndef OBJECT
#define OBJECT

Struct(Object)
{
    // Physics
    Vector2 pos;
    Vector2 velocity;

    // Rendering
    ObjectType type;
};

#endif