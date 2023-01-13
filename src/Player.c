#include "Player.h"
#include "World.h"
#include "Utils.h"

int GetPlayerLen(Player *player)
{
    // TODO
    int res = player->len;
    return res + (!(res & 1));
}

void HandleInput(Player *player, char input)
{
    player->pos -= input == 'L';
    player->pos += input == 'R';

    player->pos = maxi(player->pos, 0);
    player->pos = mini(player->pos, WIDTH - GetPlayerLen(player));
}