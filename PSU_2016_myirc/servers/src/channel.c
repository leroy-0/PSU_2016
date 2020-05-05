/*
** channel.c for channel in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 24 17:02:04 2017 leroy_0
** Last update Fri Jun  9 19:56:08 2017 yan
*/

#include	"myirc.h"

t_channel	*create_channel(t_connect *server, char *name)
{
  t_channel	*tmp;
  t_channel	*new;

  if (!(new = malloc(sizeof(t_channel))))
    return (NULL);
  new->channel = name;
  new->connected = NULL;
  new->next = NULL;
  if (!server->channel)
    server->channel = new;
  else
    {
      tmp = server->channel;
      while (tmp && tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
  return (new);
}

t_client	*find_client(t_connect *data, char *name)
{
  t_client	*user;

  user = data->client;
  while (user != NULL)
    {
      if (strcmp_insensible(user->nickname, name))
	return (user);
      user = user->next;
    }
  return (NULL);
}

int		delete_from_channel(t_channel *channel, t_client *kill)
{
  t_name	*tmp;
  t_name	*prev;
  char		print[4096];

  prev = NULL;
  tmp = channel->connected;
  while (tmp)
    {
      if (strcmp_insensible(tmp->user->nickname, kill->nickname))
	{
	  sprintf(print, "PART %s", channel->channel);
	  send_success(print, kill);
	  if (prev)
	    prev->next = tmp->next;
	  else
	    channel->connected = tmp->next;
	  free(tmp);
	  return (SUCCESS);
	}
      prev = tmp;
      tmp = tmp->next;
    }
  return (FATAL_ERROR);
}

t_channel	*find_channel(t_connect *data, char *name)
{
  t_channel	*back;

  back = data->channel;
  while (back)
    {
      if (strcmp_insensible(name, back->channel))
	return (back);
      back = back->next;
    }
  return (back);
}

void		delete_from_channels(t_connect *data, t_client *kill)
{
  t_channel	*channel;

  channel = data->channel;
  while (channel != NULL)
    {
      delete_from_channel(channel, kill);
      channel = channel->next;
    }
}
