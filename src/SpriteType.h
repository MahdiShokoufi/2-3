#include "libGolabi.h"

#ifndef SPRITETYPES
#define SPRITETYPES

enum SpriteType
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
extern const wchar_t SpriteIcons[];

#endif