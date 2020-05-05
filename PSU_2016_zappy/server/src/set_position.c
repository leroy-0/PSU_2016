/*
** set_position.c for set_position in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Fri Jun 23 12:36:44 2017 Adrien Bachelet
** Last update Sun Jul  2 20:41:44 2017 leroy_0
*/

#include	"zappy_server.h"

void		set_position(t_server *server, t_player *player,
			     int pos_x, int pos_y)
{
  (void)server;
  player->pos.x = pos_x;
  player->pos.y = pos_y;
  return ;
}
