/*
** buffer2.c for buffer2 in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Jun  9 18:31:25 2017 leroy_0
** Last update Fri Jun  9 18:34:55 2017 yan
*/

#include "common.h"

char      *get_new_buff(t_node *tmp, char *str)
{
  char    *str_tmp;

  str_tmp = str;
  if (tmp->buf)
  {
    if ((str = malloc(sizeof(char) *
      (strlen(str_tmp) + strlen(tmp->buf) + 1))) == NULL)
      return (NULL);
  }
  else
  {
    if ((str = malloc(sizeof(char) * (strlen(str_tmp) + 1))) == NULL)
      return (NULL);
  }
  str = strcpy(str, str_tmp);
  if (tmp->buf)
    str = strcat(str, tmp->buf);
  free(str_tmp);
  return (str);
}

char		*get_cmd(t_buffer *buffer)
{
  t_node	*tmp;
  char		*str;
  bool		stop;

  str = NULL;
  stop = false;
  tmp = buffer->start;
  while (!stop)
    {
      if (!str)
	str = strdup(tmp->buf);
      else
	{
if (!(str = get_new_buff(tmp, str)))
  return (NULL);
	}
      free(tmp->buf);
      tmp->buf = NULL;
      if (tmp == buffer->end)
	stop = true;
      tmp = tmp->next;
    }
  buffer->start = buffer->end;
  return (str);
}
