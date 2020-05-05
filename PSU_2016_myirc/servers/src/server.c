/*
** server.c for server in /home/yan/Documents/psu/PSU_2016_myftp
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed May 10 15:03:48 2017 yan
** Last update Fri Jun  9 18:36:12 2017 yan
*/

#include		<netdb.h>
#include		"myirc.h"

void			set_bits(t_connect *s)
{
  t_client		*a;

  FD_ZERO(&(s->fds));
  a = s->client;
  FD_SET(s->fd, &(s->fds));
  while (a != NULL)
    {
      FD_SET(a->fd, &(s->fds));
      a = a->next;
    }
}

static t_connect	*init_server(int port)
{
  t_connect		*back;
  struct protoent	*protocol;
  int			a;

  if ((back = malloc(sizeof(t_connect))) == NULL)
    return (NULL);
  back->s.sin_family = AF_INET;
  back->s.sin_port = (port == 0) ? 0 : htons(port);
  back->s.sin_addr.s_addr = INADDR_ANY;
  if ((protocol = getprotobyname("TCP")) == NULL ||
      ((back->fd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1))
    {
      free(back);
      return (NULL);
    }
  a = 1;
  setsockopt(back->fd, SOL_SOCKET, SO_REUSEADDR, (char *)&a, sizeof(a));
  if (bind(back->fd, (const struct sockaddr *)(&(back->s)),
	   sizeof(back->s)) == -1)
    {
      close(back->fd);
      free(back);
      return (NULL);
    }
  return (back);
}

static t_connect	*create_server(int port)
{
  t_connect		*back;

  if ((back = init_server(port)) == NULL)
    {
      fprintf(stderr, "Error : Connection failed\n");
      return (NULL);
    }
  if (listen(back->fd, port) == -1)
    {
      fprintf(stderr, "Error : Listening failed\n");
      free(back);
      return (NULL);
    }
  back->channel = NULL;
  back->client = NULL;
  back->max_fd = 0;
  return (back);
}

static int		run_server(t_connect *server)
{
  int			status;
  int			tmp;
  int     ret;

  status = 0;
  server->max_fd = server->fd;
  while (status != -1)
    {
      set_bits(server);
      if ((tmp = select(server->max_fd + 1, &(server->fds),
			NULL, NULL, NULL)) == -1)
	return (-1);
      if ((ret = check_client_states(server)) == FATAL_ERROR || ret == EXIT)
        return (EXIT);
    }
  return (0);
}

int			start_server(int port)
{
  t_connect		*server;

  if ((server = create_server(port)) == NULL)
    return (-1);
  else
    {
      if (run_server(server) == -1)
	return (-1);
      if (close(server->fd) == -1)
	{
	  fprintf(stderr, "Error : Close\n");
	  return (1);
	}
      free(server);
    }
  return (0);
}
