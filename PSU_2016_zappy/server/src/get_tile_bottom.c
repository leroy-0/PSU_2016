/*
** get_tile_bottom.c for get_tile_bottom in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Thu Jun 29 16:24:02 2017 Bachelet
** Last update Sat Jul  1 23:43:49 2017 Bachelet
*/

#include	"zappy_server.h"
#include	"zappy_player.h"

char		get_tile_left(t_player *player)
{
  if (player->dir == UP)
    return ('3');
  else if (player->dir == RIGHT)
    return ('5');
  else if (player->dir == LEFT)
    return ('1');
  else
    return ('7');
}

char		get_tile_bottom_left(t_player *player)
{
  if (player->dir == UP)
    return ('4');
  else if (player->dir == RIGHT)
    return ('6');
  else if (player->dir == LEFT)
    return ('2');
  else
    return ('8');
}

char		get_tile_bottom_right(t_player *player)
{
  if (player->dir == UP)
    return ('6');
  else if (player->dir == RIGHT)
    return ('8');
  else if (player->dir == LEFT)
    return ('4');
  else
    return ('2');
}

char		get_tile_bottom(t_player *player)
{
  if (player->dir == UP)
    return ('5');
  else if (player->dir == RIGHT)
    return ('7');
  else if (player->dir == LEFT)
    return ('3');
  else
    return ('1');
}
