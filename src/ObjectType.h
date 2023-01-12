#ifndef OBJECTTYPE
#define OBJECTTYPE

#include "libGolabi.h"
#include <wchar.h>

Enum(ObjectType){
    EMPTY = 0,
    BALL,
    POWER_UP,
    PlusUp,
    BRICK0,
    BRICK1,
    BRICK_ADD,
    BRICK_UP,
};

#ifdef MAIN
const wchar_t ObjectIcons[] = {L' ', L'', L'', L'烙', L'', L'', L'', L'', L'', L''};
#else
extern const wchar_t ObjectIcons[];
#endif

#endif
