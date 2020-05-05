/*
** coma_and_create_map.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/coma_and_create_map.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Fri Jun 23 07:42:47 2017 Arthur Klein
** Last update Sun Jul  2 20:43:42 2017 leroy_0
*/

#include	<string.h>
#include	<stdlib.h>
#include	<time.h>
#include	<stdbool.h>

#include	"my_malloc.h"
#include        "zappy_tile.h"
#include	"zappy_player.h"
#include	"my_add_to_str.h"

char		*get_ressources(char *info, t_tile tile)
{
  if (tile.nb_ressources[LINEMATE] > 0)
    info = my_add_to_str(info, " linemate");
  if (tile.nb_ressources[DERAUMERE] > 0)
    info = my_add_to_str(info, " deraumere");
  if (tile.nb_ressources[SIBUR] > 0)
    info = my_add_to_str(info, " sibur");
  if (tile.nb_ressources[MENDIANE] > 0)
    info = my_add_to_str(info, " mendiane");
  if (tile.nb_ressources[PHIRAS] > 0)
    info = my_add_to_str(info, " phiras");
  if (tile.nb_ressources[THYSTAME] > 0)
    info = my_add_to_str(info, " thystame");
  if (tile.nb_ressources[FOOD] > 0)
    info = my_add_to_str(info, " food");
  return (info);
}

char		*get_info_tile(t_tile tile)
{
  t_list_player	*tmp;
  char		*info;

  info = NULL;
  tmp = tile.player_list;
  while (tmp)
    {
      if (info)
	info = my_add_to_str(info, " player");
      else
	info = strdup(" player");
      tmp = tmp->next;
    }
  info = get_ressources(info, tile);
  return (info);
}

t_tile		init_ressources(t_tile *line)
{
  int		j;
  int		value;

  j = 0;
  value = 0;
  while (j < 7)
  {
    srand(j + value + clock());
    if (j == 0  && (value = rand() % 16) != 0)
      line->nb_ressources[j] = value;
   else if ((value = rand() % 2) != 0)
      line->nb_ressources[j] = value;
    else
      line->nb_ressources[j] = value;
    j++;
  }
  return (*line);
}

t_tile		*create_tile(t_tile *line, int width)
{
  int		x;
  static int	y = 0;

  x = 0;
  while (x < width)
  {
    line[x] = init_ressources(&line[x]);
    line[x].player_list = NULL;
    line[x].pos.x = x;
    line[x].pos.y = y;
    x++;
  }
  y++;
  return (line);
}

t_tile		**create_map(int width, int height)
{
  t_tile	**map;
  int		i;

  i = 0;
  if (!(map = my_malloc(sizeof(t_tile *) * height)))
    return (NULL);
  while (i < height)
    {
      if (!(map[i] = my_malloc(sizeof(t_tile) * width)))
	{
	  while (i > 0)
	    free(map[--i]);
	  free(map);
	  return (NULL);
	}
      map[i] = create_tile(map[i], width);
      i++;
    }
  return (map);
}
