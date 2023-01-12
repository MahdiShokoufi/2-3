#ifndef OBJECT
#define OBJECT

#include "libGolabi.h"
#include "Vector2.h"
#include "ObjectType.h"

Struct(Object)
{
    // Linked list
    Object *prv;
    Object *nxt;

    // Physics
    Vector2 pos;
    Vector2 velocity;

    // Rendering
    ObjectType type;

    // Gameplay
    int health;
};

#endif