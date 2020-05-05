/*
** commands.c for commands in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:54:57 2017 leroy_0
** Last update Fri Jun  9 20:17:17 2017 yan
*/

#include 	"myirc.h"

int 		cmd_server(char **cmd, t_client *client, t_connect *server)
{
  (void)cmd;
  (void)client;
  (void)server;
  return (SUCCESS);
}

int 		cmd_nick(char **cmd, t_client *client, t_connect *server)
{
  t_client 	*tmp;
  char		confirm[4096];

  if (check_func(client, false, cmd, 1) == false)
    return (SUCCESS);
  tmp = server->client;
  while (tmp)
    {
      if (tmp->nickname != NULL && strcmp(tmp->nickname, cmd[1]) == 0)
	return (send_message(client->fd, "433 nick is already in use"));
      tmp = tmp->next;
    }
  sprintf(confirm, "NICK %s:%s",
	  client->nickname ? client->nickname : "", cmd[1]);
  client->nickname = strdup(cmd[1]);
  if (client->connected == false && client->username != NULL)
    {
      sprintf(confirm, "001 : Welcome to the Internet Relay Network %s!%s@%s",
        client->nickname, client->username, client->hostname);
      client->connected = true;
      return (send_message(client->fd, confirm));
    }
  else if (client->connected != false)
    send_success(confirm, client);
  return (SUCCESS);
}

int 		cmd_list(char **cmd, t_client *client, t_connect *server)
{
  t_channel 	*tmp;
  char		print[4096];

  if (check_func(client, true, cmd, 0) == false)
    return (SUCCESS);
  if (send_message(client->fd, "321 Here comes the channel listing") == -1)
    return (FATAL_ERROR);
  tmp = server->channel;
  while (tmp)
    {
      if ((cmd[1] && strcmp_contain_insensible(tmp->channel, cmd[1]))
	  || !cmd[1])
	{
	  sprintf(print, "322 %s", tmp->channel);
	  if (send_message(client->fd, print) == -1)
	    return (FATAL_ERROR);
	}
      tmp = tmp->next;
    }
  if (send_message(client->fd, "323 channel listing done") == -1)
    return (FATAL_ERROR);
  return (SUCCESS);
}

int		cmd_join(char **cmd, t_client *client, t_connect *server)
{
  t_channel	*tmp;
  char		msg[4096];

  if (check_func(client, true, cmd, 1) == false ||
      check_channel(cmd, client) == false)
    return (SUCCESS);
  tmp = server->channel;
  sprintf(msg, "JOIN %s", cmd[1]);
  while (tmp)
    {
      if (strcmp_insensible(tmp->channel, cmd[1]))
	{
	  if (!find_client_in_channel(tmp, client->nickname))
	    new_user(tmp, client);
	  else
	    client->active_channel = tmp;
	  send_success(msg, client);
	  return (SUCCESS);
	}
      tmp = tmp->next;
    }
  tmp = create_channel(server, cmd[1]);
  new_user(tmp, client);
  send_success_own(msg, client);
  return (SUCCESS);
}

int 		cmd_part(char **cmd, t_client *client, t_connect *server)
{
  t_channel	*channel;

  if (check_func(client, true, cmd, 1) == false)
    return (SUCCESS);
  channel = server->channel;
  while (channel != NULL && !strcmp_insensible(channel->channel, cmd[1]))
    channel = channel->next;
  if (channel == NULL)
    return (send_message(client->fd, "403 channel doesn't exist"));
  else
    {
      if (client->active_channel == NULL ||
	  delete_from_channel(channel, client) == -1)
        return (send_message(client->fd, "403 Not connected to this channel"));
      if (client->active_channel == channel)
	client->active_channel = NULL;
      return (SUCCESS);
    }
  return (SUCCESS);
}
