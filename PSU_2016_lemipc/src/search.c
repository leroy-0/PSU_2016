/*
** search.c for search in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:23:16 2017 leroy_0
** Last update Sun Apr  2 18:23:16 2017 leroy_0
*/

#include	<string.h>
#include	<stdlib.h>
#include	"lemipc.h"

t_enemy   *search_enemy3(t_game *game, int pos, char id, t_enemy *enemy)
{
    if (pos + 31 < (int)strlen(game->addr) && game->addr[pos + 31] > '0'
        && game->addr[pos + 31] != id)
    {
        enemy->pos = pos + 31;
        enemy->dir = DOWN_L;
    }
    if (pos + 33 < (int)strlen(game->addr) && game->addr[pos + 33] > '0'
        && game->addr[pos + 33] != id)
    {
        enemy->pos = pos + 33;
        enemy->dir = DOWN_R;
    }
    if (enemy->pos == -1)
        return (NULL);
      return (enemy);
}

t_enemy   *search_enemy2(t_game *game, int pos, char id, t_enemy *enemy)
{
  if (pos - 32 >= 0 && game->addr[pos - 32] > '0'
        && game->addr[pos - 32] != id)
    {
        enemy->pos = pos - 32;
        enemy->dir = UP;
    }
    if (pos + 32 < (int)strlen(game->addr) && game->addr[pos + 32] > '0'
        && game->addr[pos + 32] != id)
    {
        enemy->pos = pos + 32;
        enemy->dir = DOWN;
    }
    if (pos - 31 >= 0 && game->addr[pos - 31] > '0'
        && game->addr[pos - 31] != id)
    {
        enemy->pos = pos - 31;
        enemy->dir = UP_R;
    }
    if (pos - 33 >= 0 && game->addr[pos - 33] > '0'
        && game->addr[pos - 33] != id)
    {
        enemy->pos = pos - 33;
        enemy->dir = UP_L;
    }
    return (search_enemy3(game, pos, id, enemy));
}

t_enemy		*search_enemy(t_game *game, int pos, char id)
{
    t_enemy	*enemy;

    enemy = malloc(sizeof(t_enemy));
    if (!enemy)
        return (NULL);
    enemy->pos = -1;

    if ((pos % 32) + 1 < 32 && game->addr[pos + 1] > '0'
        && game->addr[pos + 1] != id)
    {
        enemy->pos = pos + 1;
        enemy->dir = RIGHT;
    }
    if ((pos % 32) - 1 >= 0 && game->addr[pos - 1] > '0'
        && game->addr[pos - 1] != id)
    {
        enemy->pos = pos - 1;
        enemy->dir = LEFT;
    }
    return (search_enemy2(game, pos, id, enemy));
}
