/*
** utils_next.c for utils_next in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Fri Jun 23 14:36:50 2017 Adrien Bachelet
** Last update Sun Jul  2 19:31:38 2017 yan
*/

#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdbool.h>
#include	"zappy_server.h"
#include	"zappy_list_player.h"
#include	"zappy_tile.h"
#include	"my_malloc.h"

bool		elevation_success(t_server *server, t_player *player)
{
  char		*message;
  char		level[2];
  char		msg[MSG_LENGTH];

  message = NULL;
  message = strdup("Current level: ");
  level[0] = player->elevation + '0';
  level[1] = '\0';
  message = my_add_to_str(message, level);
  send_message(player->fd, message);
  sprintf(msg, "plv %d", player->id);
  send_graphical(server, msg);
  return (true);
}

int		count_nb_player(t_tile tile)
{
  int		cpt;
  t_list_player	*tmp;

  cpt = 0;
  tmp = tile.player_list;
  while (tmp)
    {
      cpt++;
      tmp = tmp->next;
    }
  return (cpt);
}

void        *my_malloc(int size)
{
  void      *ptr;

  if (!(ptr = malloc(size)))
    {
      fprintf(stderr, "Error : malloc failure\n");
      return (NULL);
    }
  return (ptr);
}

char        *my_add_to_str(char *src, char *to_add)
{
  char      *new;

  new = NULL;
  if (src == NULL)
    new = strdup(to_add);
  else if (to_add == NULL)
    return (src);
  else
    {
      if (new == NULL &&
	  !(new = my_malloc(sizeof(char) * (strlen(src) + strlen(to_add) + 1))))
	return (NULL);
      new[0] = '\0';
      strcat(new, src);
      free(src);
      strcat(new, to_add);
    }
  return (new);
}
