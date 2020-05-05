/*
** get_tile_top.c for get_tile_top in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Thu Jun 29 16:09:14 2017 Bachelet
** Last update Sat Jul  1 23:42:27 2017 Bachelet
*/

#include	"zappy_server.h"
#include	"zappy_player.h"

char		get_tile_right(t_player *player)
{
  if (player->dir == UP)
    return ('7');
  else if (player->dir == RIGHT)
    return ('1');
  else if (player->dir == LEFT)
    return ('5');
  else
    return ('3');
}

char		get_tile_top_right(t_player *player)
{
  if (player->dir == UP)
    return ('8');
  else if (player->dir == RIGHT)
    return ('2');
  else if (player->dir == LEFT)
    return ('6');
  else
    return ('4');
}

char		get_tile_top_left(t_player *player)
{
  if (player->dir == UP)
    return ('2');
  else if (player->dir == RIGHT)
    return ('4');
  else if (player->dir == LEFT)
    return ('8');
  else
    return ('6');
}

char		get_tile_top(t_player *player)
{
  if (player->dir == UP)
    return ('1');
  else if (player->dir == RIGHT)
    return ('3');
  else if (player->dir == LEFT)
    return ('7');
  else
    return ('5');
}
