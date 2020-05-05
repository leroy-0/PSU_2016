/*
** make_elevation.c for make_elevation in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Sun Jul  2 21:52:48 2017 Bachelet
** Last update Sun Jul  2 22:06:42 2017 Bachelet
*/

#include		"zappy_server.h"

void			make_elevation(t_tile *tile, t_server *server)
{
  t_list_player		*tmp;
  int			i;

  i = 1;
  tmp = tile->player_list;
  while (tmp)
    {
      tmp->player->elevation++;
      elevation_success(server, tmp->player);
      tmp = tmp->next;
    }
  while (i < 7)
    tile->nb_ressources[i++] = 0;
  return ;
}
