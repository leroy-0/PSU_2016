/*
** commands4.c for commands4 in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Fri Jun  9 18:22:54 2017 yan
** Last update Fri Jun  9 20:03:55 2017 yan
*/

#include	"myirc.h"

void		cmd_info_curent(t_connect *server)
{
  t_channel	*channel;
  t_name	*name;
  t_client	*client;

  printf("---Server info---\n\n---> Channels created :\n");
  channel = server->channel;
  while (channel != NULL)
    {
      printf("     -> %s\n", channel->channel);
      name = channel->connected;
      while (name != NULL)
        {
          printf("     ---> %s\n", name->user->nickname);
          name = name->next;
        }
      channel = channel->next;
    }
  client = server->client;
  printf("\n---> Users connected :\n");
  while (client != NULL)
    {
      printf("     -> %s\n", client->nickname);
      client = client->next;
    }
  printf("----------------\n");
}

void		send_success(char *confirm, t_client *client)
{
  char		*cmd[] = {confirm, NULL};

  send_to_all(client->active_channel, cmd, client->nickname);
  send_msg(client->nickname, client->fd, cmd, 0);
}

void		send_success_own(char *confirm, t_client *client)
{
  char		*cmd[] = {confirm, NULL};

  send_msg(client->nickname, client->fd, cmd, 0);
}

bool		check_func(t_client *client, bool connected,
			   char **cmd, int num_param)
{
  int		a;

  if ((client->username == NULL || client->nickname == NULL) &&
      connected == true)
    {
      send_message(client->fd, "451 User needs to be connected");
      return (false);
    }
  a = 1;
  while (cmd && cmd[a])
    a++;
  if (a <= num_param)
    {
      send_message(client->fd, "461 wrong number of parameters");
      return (false);
    }
  return (true);
}

bool		check_channel(char **cmd, t_client *client)
{
  if (cmd[1][0] != '#')
    {
      send_message(client->fd, "403 channel name must start with a #");
      return (false);
    }
  return (true);
}
