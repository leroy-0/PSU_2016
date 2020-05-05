/*
** tools.c for tools in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Jun  9 18:21:05 2017 leroy_0
** Last update Fri Jun  9 18:21:05 2017 leroy_0
*/

#include "myirc.h"

char      *get_msg(t_node **buffer)
{
  t_node  *tmp;
  t_node  *prev;
  char    *msg;

  if ((msg = malloc(sizeof(char) * MAX_PATH)) == NULL)
    return (NULL);
  msg[0] = '\0';
  tmp = *buffer;
  while (tmp)
  {
    strcat(msg, tmp->buf);
    prev = tmp;
    tmp = tmp->next;
    free(prev);
  }
  *buffer = NULL;
  return (msg);
}

t_node           *get_buffer(t_node *buffer, char *str)
{
  t_node         *node;
  t_node         *tmp;

  if ((node = malloc(sizeof(t_node))) == NULL)
    return (NULL);
  node->buf = str;
  node->next = NULL;
  if (!buffer)
    buffer = node;
  else
  {
    tmp = buffer;
    while (tmp && tmp->next)
      tmp = tmp->next;
    tmp->next = node;
  }
  return (buffer);
}

char      *epur_string(char *str)
{
  static t_node  *buffer = NULL;
  bool    end;
  int     x;

  x = 0;
  end = false;
  while (str && str[x] != '\0')
  {
    if (str[x] == '\r' && str[x + 1] && str[x + 1] == '\n'
      && str[x + 2] == '\0')
    {
      end = true;
      str[x] = '\0';
    }
    x++;
  }
  if (!(buffer = get_buffer(buffer, str)))
    return (NULL);
  if (end)
    return (get_msg(&buffer));
  return (NULL);
}
