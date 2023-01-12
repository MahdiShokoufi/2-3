#include "PowerUp.h"

int isActive(PowerUp p, double ttime)
{
    return p.endtime >= ttime;
}