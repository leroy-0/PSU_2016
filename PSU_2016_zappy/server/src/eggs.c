/*
** eggs.c for eggs in /home/tekm/tek2/PSU_2016_zappy
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Jul  2 20:39:24 2017 leroy_0
** Last update Sun Jul  2 20:39:25 2017 leroy_0
*/

#include		"zappy_parsing.h"
#include		"zappy_player.h"

t_eggs			*init_eggs_list(t_eggs *list)
{

  list = x_malloc(sizeof(t_eggs));
  list->id = 0;
  list->activate = false;
  list->next = NULL;
  return (list);
}

t_eggs			*init_eggs_node(t_eggs *list)
{
  static int		i = 1;
  t_eggs		*node;
  t_eggs		*tmp;

  tmp = list;
  node = x_malloc(sizeof(t_eggs));
  node->id = i++;
  node->activate = false;
  node->next = NULL;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = node;
  return (list);
}
