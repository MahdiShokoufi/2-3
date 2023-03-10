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
    int exist;

    // Physics
    Vector2 pos;
    Vector2 velocity;

    // Rendering
    ObjectType type;

    // Gameplay
    int health;
    int spell;
};

#endif