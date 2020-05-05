/*
** look_top.c for look_top in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Wed Jun 21 12:41:07 2017 Adrien Bachelet
** Last update Fri Jun 30 13:27:39 2017 Bachelet
*/

#include	<stdlib.h>
#include	<string.h>
#include	"zappy_server.h"
#include	"zappy_player.h"
#include        "zappy_tile.h"
#include	"my_add_to_str.h"

static char	*get_info_line_top(t_pos *pos, t_server *server, int size,
				   char *data)
{
  int           i;
  t_tile	**map;
  char		*tmp;

  i = 0;
  map = server->map;
  while (i < size)
    {
      if (data[1] != '\0' && !(data = my_add_to_str(data, ",")))
	return (NULL);
      if (pos->x + i < server->info.width)
        tmp = get_info_tile(map[pos->y][pos->x + i++]);
      else
	tmp = get_info_tile(map[pos->y][pos->x - server->info.width + i++]);
      if (!(data = my_add_to_str(data, tmp)))
        {
	  free(data);
	  free(tmp);
	  return (NULL);
        }
      free(tmp);
    }
  return (data);
}

char		*look_top(t_player *player, t_server *server)
{
  int		size;
  t_pos		tmp;
  char		length;
  char		*data;

  size = 1;
  length = 0;
  data = strdup("[");
  tmp.x = player->pos.x;
  tmp.y = player->pos.y;
  while (length++ <= player->elevation)
    {
      if (!(data = get_info_line_top(&tmp, server, size, data)))
	return (NULL);
      tmp.y = (tmp.y == 0) ? (server->info.height - 1) : (tmp.y - 1);
      tmp.x = (tmp.x == 0) ? (server->info.width - 1) : (tmp.x - 1);
      size += 2;
    }
  if (!(data = my_add_to_str(data, " ]")))
    return (NULL);
  return (data);
}
