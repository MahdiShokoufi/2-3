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

#ifdef MAIN
const wchar_t SpriteIcons[] = {L' ', L'', L'', L'烙', L' ', L' ', L' ', L''};
#else
extern const wchar_t SpriteIcons[];
#endif

#endif
