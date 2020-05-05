/*
** exec.c for exec in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 24 15:29:32 2017 leroy_0
** Last update Fri Jun  9 18:35:38 2017 yan
*/

#include	 "myirc.h"

int		get_max_fd(t_connect *s)
{
  t_client	*a;
  int		back;

  if (s == NULL)
    return (-1);
  back = s->fd;
  if (s->client == NULL)
    return (back);
  a = s->client;
  while (a != NULL)
    {
      if (a->fd > back)
	back = a->fd;
      a = a->next;
    }
  return (back);
}

int		execute_client(t_client *a, t_connect *s)
{
  char		*cmd;
  char		**cmds;
  int		status;
  int		x;

  if (!(cmd = get_cmd(a->buffer)))
    return (FATAL_ERROR);
  cmd = epur_str(cmd);
  cmds = my_strtab(cmd, "\r\n");
  x = 0;
  while (cmds[x])
    {
      printf("command = [%s]\n", cmds[x]);
      if ((status = manage_commands(cmds[x], a, s)) == FATAL_ERROR ||
	  status == EXIT)
	return (status);
      x++;
    }
  return (SUCCESS);
}

void		free_client_info(t_client *kill)
{
  free(kill->buffer);
  if (kill->nickname != NULL)
    free(kill->nickname);
  if (kill->username != NULL)
    free(kill->username);
  if (kill->hostname != NULL)
    free(kill->hostname);
  close(kill->fd);
}

void		delete_client(t_connect *data, t_client *kill)
{
  t_client	*client;
  t_client	*before;
  t_client	*next;

  before = NULL;
  client = data->client;
  delete_from_channels(data, kill);
  printf("%s disconnected\n", kill->nickname);
  while (client != NULL)
    {
      next = client->next;
      if (client == kill)
	{
	  if (before == NULL)
	    data->client = NULL;
	  else
	    before->next = client->next;
	  free_client_info(kill);
	  if (before == NULL)
	    data->client = next;
	}
      before = client;
      client = next;
    }
}

int		check_client_states(t_connect *s)
{
  t_client	*a;
  int		ret;
  int		status;

  if (FD_ISSET(s->fd, &(s->fds)))
    create_client(s);
  a = s->client;
  while (a != NULL)
    {
      status = 0;
      if (FD_ISSET(a->fd, &(s->fds)))
	{
	  if (circular_buff(a->buffer, a->fd, &status) != NULL)
	    {
	      if ((ret = execute_client(a, s)) == FATAL_ERROR || ret == EXIT)
		return (ret);
	    }
	  else if (status == -1)
	    delete_client(s, a);
	}
      a = a->next;
    }
  return (SUCCESS);
}
