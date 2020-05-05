/*
** attack.c for attack in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:19:51 2017 leroy_0
** Last update Sun Apr  2 18:20:00 2017 leroy_0
*/

#include  <string.h>
#include  <stdlib.h>
#include "lemipc.h"

t_pos   attack_enemy4(t_game *game, t_enemy *enemy, t_pos result)
{
    if (enemy->dir == LEFT)
    {
      if (enemy->pos + UP_L >= 0
        && game->addr[enemy->pos + UP_L] == '0')
  result = pos_to_x_y(enemy->pos + UP_L);
      else if (enemy->pos + DOWN_L < (int)strlen(game->addr)
        && game->addr[enemy->pos + DOWN_L] == '0')
  result = pos_to_x_y(enemy->pos + DOWN_L);
    }
    else if (enemy->dir == UP_R)
    {
      if (enemy->pos + UP >= 0
        && game->addr[enemy->pos + UP] == '0')
  result = pos_to_x_y(enemy->pos + UP);
      else if (enemy->pos + RIGHT < (int)strlen(game->addr)
        && game->addr[enemy->pos + RIGHT] == '0')
  result = pos_to_x_y(enemy->pos + RIGHT);
    }
    return (result);
}

t_pos   attack_enemy3(t_game *game, t_enemy *enemy, t_pos result)
{
    if (enemy->dir == DOWN_L)
    {
      if (enemy->pos + LEFT >= 0
        && game->addr[enemy->pos + LEFT] == '0')
  result = pos_to_x_y(enemy->pos + LEFT);
      else if (enemy->pos + DOWN < (int)strlen(game->addr)
        && game->addr[enemy->pos + DOWN] == '0')
  result = pos_to_x_y(enemy->pos + DOWN);
    }
  else if (enemy->dir == DOWN_R)
    {
      if (enemy->pos + RIGHT < (int)strlen(game->addr)
        && game->addr[enemy->pos + RIGHT] == '0')
  result = pos_to_x_y(enemy->pos + RIGHT);
      else if (enemy->pos + DOWN < (int)strlen(game->addr)
        && game->addr[enemy->pos + DOWN] == '0')
  result = pos_to_x_y(enemy->pos + DOWN);
    }
    return (attack_enemy4(game, enemy, result));
}

t_pos   attack_enemy2(t_game *game, t_enemy *enemy, t_pos result)
{
  if (enemy->dir == RIGHT)
    {
      if (enemy->pos + UP_R >= 0
        && game->addr[enemy->pos + UP_R] == '0')
  result = pos_to_x_y(enemy->pos + UP_R);
      else if (enemy->pos + DOWN_R < (int)strlen(game->addr)
        && game->addr[enemy->pos + DOWN_R] == '0')
  result = pos_to_x_y(enemy->pos + DOWN_R);
    }
  else if (enemy->dir == UP_L)
    {
      if (enemy->pos + LEFT >= 0
        && game->addr[enemy->pos + LEFT] == '0')
  result = pos_to_x_y(enemy->pos + LEFT);
      else if (enemy->pos + UP >= 0
        && game->addr[enemy->pos + UP] == '0')
  result = pos_to_x_y(enemy->pos + UP);
    }
    return (attack_enemy3(game, enemy, result));
}

t_pos		attack_enemy(t_game *game, t_enemy *enemy)
{
  t_pos		result;

  result = pos_to_x_y(game->pos_player);
  if (enemy->dir == UP)
    {
      if (enemy->pos + LEFT >= 0
        && game->addr[enemy->pos + LEFT] == '0')
	result = pos_to_x_y(enemy->pos + LEFT);
      else if (enemy->pos + RIGHT < (int)strlen(game->addr)
        && game->addr[enemy->pos + RIGHT] == '0')
	result = pos_to_x_y(enemy->pos + RIGHT);
    }
  else if (enemy->dir == DOWN)
    {
      if (enemy->pos + DOWN_L < (int)strlen(game->addr)
        && game->addr[enemy->pos + DOWN_L] == '0')
	result = pos_to_x_y(enemy->pos + DOWN_L);
      else if (enemy->pos + DOWN_R < (int)strlen(game->addr)
        && game->addr[enemy->pos + DOWN_R] == '0')
	result = pos_to_x_y(enemy->pos + DOWN_R);
    }
    return (attack_enemy2(game, enemy, result));
}
