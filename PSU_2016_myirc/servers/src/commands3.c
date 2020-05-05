/*
** commands3.c for commands3 in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 18:07:02 2017 leroy_0
** Last update Fri Jun  9 19:45:58 2017 yan
*/

#include <fcntl.h>
#include "myirc.h"

int 		cmd_quit(char **cmd, t_client *client, t_connect *server)
{
  char  msg[4096];

  sprintf(msg, "quit :%s", client->nickname);
  cmd[0] = msg;
  cmd[1] = NULL;
  send_to_all(client->active_channel, cmd, client->nickname);
  if (send_message(client->fd, msg) == FATAL_ERROR)
    return (FATAL_ERROR);
  delete_client(server, client);
  return (SUCCESS);
}

int 		cmd_help(char **cmd, t_client *client, t_connect *server)
{
  char	msg[MAX_PATH];
  int 	fd;
  int 	r;

  (void)cmd;
  (void)server;
  if ((fd = open("help", O_RDONLY)) == -1
      || (r = read(fd, msg, sizeof(msg))) == -1)
    return (FILE_FAIL);
  msg[r] = '\0';
  if (send_message(client->fd, "704 start of help") == -1 ||
      send_message(client->fd, msg) == -1 ||
      send_message(client->fd, "706 end of help") == -1)
    return (FATAL_ERROR);
  return (SUCCESS);
}

int     cmd_active(char **cmd, t_client *client, t_connect *server)
{
  (void)cmd;
  (void)server;
  if (client->active_channel)
  {
    if (send_message(client->fd, "CHANNEL/") == FATAL_ERROR)
      return (FATAL_ERROR);
    return (send_message(client->fd, client->active_channel->channel));
  }
  return (send_message(client->fd, "NO_CHANNEL/"));
}

int 		cmd_other(char **cmd, t_client *client, t_connect *server)
{
  t_channel 	*tmp;
  t_name	*tmp_c;

  if (check_func(client, true, cmd, 0) == false)
    return (0);
  if (!client->active_channel)
    return (send_message(client->fd, "442 Not connected to any channel"));
  tmp = server->channel;
  while (tmp)
    {
      if (strcmp_insensible(tmp->channel, client->active_channel->channel))
	{
	  tmp_c = tmp->connected;
	  while (tmp_c)
	    {
	      if (strcmp_insensible(tmp_c->user->nickname, client->nickname))
		send_to_all(tmp, cmd, client->nickname);
	      tmp_c = tmp_c->next;
	    }
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int		cmd_user(char **cmd, t_client *client, t_connect *server)
{
  char		confirm[4096];

  (void)server;
  if (check_func(client, false, cmd, 4) == false)
    return (0);
  client->username = strdup(cmd[1]);
  client->hostname = strdup(cmd[2]);
  if (client->connected == false && client->nickname != NULL)
  {
    sprintf(confirm, "001 : Welcome to the Internet Relay Network %s!%s@%s",
	    client->nickname, client->username, client->hostname);
    client->connected = true;
    return (send_message(client->fd, confirm));
  }
  return (SUCCESS);
}
