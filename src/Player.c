#include "Player.h"
#include "World.h"
#include "Utils.h"
#include <assert.h>
#include "PowerUp.h"

int GetPlayerLen(Player *player, double ttime)
{
    int res = player->len;
    if (isActive(player->incSize, ttime))
        res *= 3;
    if (isActive(player->decSize, ttime))
        res = res * 2 / 3;
    res = res + (!(res & 1));

    player->pos = maxi(player->pos, 0);
    player->pos = mini(player->pos, WIDTH - res);

    return res;
}

void HandleInput(Player *player, char input, double ttime)
{
    int speed = 2;
    if (isActive(player->incSpeed, ttime))
        speed *= 2;
    if (isActive(player->decSpeed, ttime))
        speed /= 2;
    if (isActive(player->reverseInput, ttime))
        speed *= -1;
    speed = -speed * (input == 'L') + speed * (input == 'R');
    player->pos += speed;

    player->pos = maxi(player->pos, 0);
    player->pos = mini(player->pos, WIDTH - GetPlayerLen(player, ttime));
}