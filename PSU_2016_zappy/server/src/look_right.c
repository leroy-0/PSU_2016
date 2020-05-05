/*
** look_right.c for look_right in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Wed Jun 21 15:09:08 2017 Adrien Bachelet
** Last update Sun Jul  2 12:27:59 2017 yan
*/

#include	<stdlib.h>
#include	<string.h>
#include	"zappy_server.h"
#include	"zappy_player.h"
#include        "zappy_tile.h"
#include	"my_add_to_str.h"

static char	*get_info_line_right(t_pos *pos, t_server *server, int size,
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
      if (pos->y + i < server->info.height)
	tmp = get_info_tile(map[pos->y + i++][pos->x]);
      else
	tmp = get_info_tile(map[pos->y - server->info.height + i++][pos->x]);
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

char		*look_right(t_player *player, t_server *server)
{
  int           size;
  t_pos		tmp;
  char		lenght;
  char          *data;

  size = 1;
  lenght = 0;
  data = strdup("[");
  tmp.x = player->pos.x;
  tmp.y = player->pos.y;
  while (lenght++ <= player->elevation)
    {
      if (!(data = get_info_line_right(&tmp, server, size, data)))
	return (NULL);
      tmp.y = (tmp.y == 0) ? (server->info.height - 1) : (tmp.y - 1);
      tmp.x = (tmp.x == server->info.width - 1) ? (0) : (tmp.x + 1);
      size += 2;
    }
  if (!(data = my_add_to_str(data, " ]")))
    return (NULL);
  return (data);
}
