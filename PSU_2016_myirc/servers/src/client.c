/*
** client.c for client in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Mon May 22 14:52:25 2017 yan
** Last update Fri Jun  9 18:01:07 2017 yan
*/

#include	"myirc.h"

bool			check_client(t_connect *data, char *name)
{
  t_client		*tmp;

  tmp = data->client;
  while (tmp != NULL)
    {
      if (tmp->nickname != NULL && strcmp(name, tmp->nickname) == 0)
	return (false);
      tmp = tmp->next;
    }
  return (true);
}

t_client		*init_client(t_connect *s)
{
  static int		nb_clients = 1;
  t_client		*back;

  if ((back = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  back->s_size = sizeof(back);
  back->username = NULL;
  back->nickname = NULL;
  back->hostname = NULL;
  nb_clients++;
  if (!(back->buffer = create_buffer()) ||
      (back->fd = accept(s->fd, (struct sockaddr *)(&(back->s)),
			 &(back->s_size))) == -1)
    {
      fprintf(stderr, "Error : accept failed\n");
      free(back);
      return (NULL);
    }
  back->next = NULL;
  back->active_channel = NULL;
  back->file = NULL;
  back->connected = false;
  printf("New client authentication\n");
  return (back);
}

int			create_client(t_connect *s)
{
  t_client		*back;
  t_client		*tmp;

  if ((back = init_client(s)) == NULL)
    return (-1);
  if (!s->client)
    s->client = back;
  else
  {
    tmp = s->client;
    while (tmp && tmp->next)
      tmp = tmp->next;
    tmp->next = back;
  }
  s->max_fd = get_max_fd(s);
  return (0);
}

t_name		*new_user(t_channel *channel, t_client *a)
{
  t_name	*tmp;
  t_name	*new;

  if (!(new = malloc(sizeof(t_name))))
    return (NULL);
  a->active_channel = channel;
  new->user = a;
  new->next = NULL;
  if (!channel->connected)
    channel->connected = new;
  else
    {
      tmp = channel->connected;
      while (tmp && tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
  return (new);
}
