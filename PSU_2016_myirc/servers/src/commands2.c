/*
** commands2.c for commands in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:55:03 2017 leroy_0
** Last update Fri Jun  9 20:02:01 2017 yan
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"fnc_ptrs.h"
#include	"myirc.h"

int		cmd_users(char **cmd, t_client *client, t_connect *server)
{
  t_client	*tmp;
  char		print[4096];

  if (check_func(client, true, cmd, 0) == false)
    return (SUCCESS);
  if (server->client == NULL ||
      (server->client == client && server->client->next == NULL))
    return (send_message(client->fd, "395 nobody is logged in"));
  if (send_message(client->fd, "392 Here comes the users listing") == -1)
    return (FATAL_ERROR);
  tmp = server->client;
  while (tmp)
    {
      if (client->nickname && tmp->nickname
	  && strcmp(client->nickname, tmp->nickname) != 0)
	{
	  sprintf(print, "393 %s", tmp->nickname);
	  if (send_message(client->fd, print) == -1)
	    return (FATAL_ERROR);
	}
      tmp = tmp->next;
    }
  return (send_message(client->fd, "394 users listing done"));
}

int		cmd_msg(char **cmd, t_client *client, t_connect *server)
{
  t_client	*receive;

  if (check_func(client, true, cmd, 0) == true)
    {
      if (cmd[1] && cmd[2] && cmd[3])
	return (cmd_send_file(cmd, client, server));
      else if (cmd[1] && cmd[2])
	{
	  if ((receive = find_client(server, cmd[1])) != NULL)
	    send_msg(client->nickname, receive->fd, cmd, 2);
	  else
	    return (send_message(client->fd, "401 User doesn't exist"));
	}
      else
	return (send_message(client->fd, "461 wrong number of parameters"));
    }
  return (SUCCESS);
}

int		cmd_send_file(char **cmd, t_client *client, t_connect *server)
{
  (void)cmd;
  (void)client;
  (void)server;
  return (SUCCESS);
}

int		cmd_names(char **cmd, t_client *client, t_connect *server)
{
  t_name	*tmp;
  t_channel	*channel;
  char		print[4096];

  if (check_func(client, true, cmd, 1) == false)
    return (0);
  if (cmd == NULL || cmd[1] == NULL ||
      (channel = find_channel(server, cmd[1])) == NULL)
    send_message(client->fd, "403 channel doesn't exist");
  else
    {
      tmp = channel->connected;
      sprintf(print, "353 %s", channel->channel);
      if (send_message(client->fd, print) == -1)
	return (FATAL_ERROR);
      while (tmp)
	{
	  if (send_message(client->fd, tmp->user->nickname) == -1)
	    return (FATAL_ERROR);
	  tmp = tmp->next;
	}
      return (send_message(client->fd, "366 channel listing done"));
    }
  return (SUCCESS);
}

int 		cmd_accept_file(char **cmd, t_client *client, t_connect *server)
{
  (void)cmd;
  (void)server;
  if (check_func(client, true, cmd, 1) == false)
    return (0);
  return (send_message(client->fd, "XXX Successfully accepted file"));
}
