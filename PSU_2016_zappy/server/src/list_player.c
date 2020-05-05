/*
** list_player.c for list_player in /home/tekm/tek2/PSU_2016_zappy
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Jul  2 20:39:36 2017 leroy_0
** Last update Sun Jul  2 20:39:36 2017 leroy_0
*/

#include	<stdlib.h>
#include	"zappy_list_player.h"
#include	"zappy_server.h"

t_list_player	*create_list_player(t_player *player)
{
  t_list_player	*back;

  if ((back = malloc(sizeof(t_list_player))) == NULL)
    {
      fprintf(stderr, "Error: Malloc failed\n");
      return (NULL);
    }
  back->player = player;
  back->next = NULL;
  return (back);
}

void		add_list_player(t_list_player **list, t_list_player *create)
{
  t_list_player	*tmp;

  if (create != NULL)
  {
    tmp = *list;
    if (tmp == NULL)
      *list = create;
    else
    {
      while (tmp && tmp->next)
	tmp = tmp->next;
      tmp->next = create;
    }
  }
}
