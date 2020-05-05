/*
** alive.c for alive in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:16:27 2017 leroy_0
** Last update Sun Apr  2 18:16:37 2017 leroy_0
*/

#include <string.h>
#include <stdlib.h>
#include "lemipc.h"

bool		check_ids(t_game *game, int *enemy)
{
  bool		alive;
  int		z;
  int		x;

  x = 0;
  z = 0;
  alive = true;
  while (x < 4)
    {
      z = x + 1;
      while (z < 4)
        {
	  if (enemy[z] != -1 && enemy[x] != -1
	      && game->addr[enemy[x]] == game->addr[enemy[z]])
	    alive = false;
	  z++;
        }
      x++;
    }
  return (alive);
}

int     *is_alive2(t_game *game, int *enemy, int x)
{
  if ((int)game->pos_player - 32 > 0
      && game->addr[game->pos_player - 32] > '0'
      && game->addr[game->pos_player - 32] != game->team_id + '0')
    {
      enemy[x] = game->pos_player - 32;
      x++;
    }
  if ((int)game->pos_player + 32 < (int)strlen(game->addr)
      && game->addr[game->pos_player + 32] > '0'
      && game->addr[game->pos_player + 32] != game->team_id + '0')
    {
      enemy[x] = game->pos_player + 32;
      x++;
    }
    return (enemy);
}

int     *init_enemy()
{
  int   *enemy;

  enemy = malloc(sizeof(int) * 4);
  if (!enemy)
    exit(84);
  enemy[0] = -1;
  enemy[1] = -1;
  enemy[2] = -1;
  enemy[3] = -1;
  return (enemy);
}

bool		is_alive(t_game *game)
{
  bool  result;
  int		*enemy;
  int		x;

  x = 0;
  enemy = init_enemy();
  if ((int)game->pos_player + 1 < (int)strlen(game->addr)
      && game->addr[game->pos_player + 1] > '0'
      && game->addr[game->pos_player + 1] != game->team_id + '0')
    {
      enemy[x] = game->pos_player + 1;
      x++;
    }
  if ((int)game->pos_player - 1 > 0
      && game->addr[game->pos_player - 1] > '0'
      && game->addr[game->pos_player - 1] != game->team_id + '0')
    {
      enemy[x] = game->pos_player - 1;
      x++;
    }
  enemy = is_alive2(game, enemy, x);
  result = check_ids(game, enemy);
  free(enemy);
  return (result);
}
