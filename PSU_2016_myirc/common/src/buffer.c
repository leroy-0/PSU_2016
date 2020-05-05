/*
** buffer.c for buffer in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Jun  9 18:31:35 2017 leroy_0
** Last update Fri Jun  9 18:31:35 2017 leroy_0
*/

#include	"common.h"

t_node		*new_node(char *buff, t_node *prev)
{
  t_node	*node;

  if ((node = malloc(sizeof(t_node))) == NULL)
    return (NULL);
  node->buf = buff;
  if (prev != NULL)
    {
      node->next = prev->next;
      prev->next = node;
    }
  else
    node->next = node;
  return (node);
}

t_buffer	*create_buffer()
{
  t_buffer	*buff;

  if ((buff = malloc(sizeof(t_buffer))) == NULL)
    return (NULL);
  buff->start = new_node(NULL, NULL);
  buff->end = buff->start;
  return (buff);
}

void		allocate_node(t_buffer *buffer, char *buf)
{
  if (buffer->start == buffer->end->next && buffer->start->buf != NULL)
    new_node(buf, buffer->end);
  else
    {
      if (buffer->end->buf != NULL)
	free(buffer->end->buf);
      buffer->end->buf = buf;
    }
  buffer->end = buffer->end->next;
}

char		*circular_buff(t_buffer *buffer, int fd, int *status)
{
  char		*buf;
  int		r;

  if ((buf = malloc(sizeof(char) * NAME_LENGTH)) == NULL)
    return (NULL);
  if ((r = recv(fd, buf, NAME_LENGTH, 0)) <= 0)
    {
      *status = -1;
      return (NULL);
    }
  buf[r] = '\0';
  allocate_node(buffer, buf);
  if (buf[strlen(buf) - 1] == '\n' || buf[strlen(buf) - 1] == '\r')
    {
      buf[strlen(buf) - 1] = '\0';
      if (strlen(buf) > (unsigned int)0 &&
	  (buf[strlen(buf) - 1] == '\n' || buf[strlen(buf) - 1] == '\r'))
	buf[strlen(buf) - 1] = '\0';
      return (buf);
    }
  return (NULL);
}
