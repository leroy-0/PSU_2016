/*
** look_left.c for look_left in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Wed Jun 21 15:20:54 2017 Adrien Bachelet
** Last update Sun Jul  2 12:22:36 2017 yan
*/

#include	<stdlib.h>
#include	<string.h>
#include	"zappy_server.h"
#include	"zappy_player.h"
#include        "zappy_tile.h"
#include	"my_add_to_str.h"

static char	*get_info_line_left(t_pos *pos, t_server *server, int size,
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
      if (pos->y - i < 0)
        tmp = get_info_tile(map[pos->y + server->info.height - i++][pos->x]);
      else
        tmp = get_info_tile(map[pos->y - i++][pos->x]);
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

char            *look_left(t_player *player, t_server *server)
{
  int           size;
  t_pos		tmp;
  char		length;
  char          *data;

  size = 1;
  length = 0;
  data = strdup("[");
  tmp.x = player->pos.x;
  tmp.y = player->pos.y;
  while (length++ <= player->elevation)
    {
      if (!(data = get_info_line_left(&tmp, server, size, data)))
	return (NULL);
      tmp.y = (tmp.y == server->info.height - 1) ? (0) : (tmp.y + 1);
      tmp.x = (tmp.x == 0) ? (server->info.width - 1) : (tmp.x - 1);
      size += 2;
    }
  if (!(data = my_add_to_str(data, " ]")))
    return (NULL);
  return (data);
}
