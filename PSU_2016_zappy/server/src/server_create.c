/*
** server_create.c for server_create in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 15:46:11 2017 yan
** Last update Sun Jul  2 16:39:23 2017 yan
*/

#include		<netdb.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netinet/in.h>
#include		"zappy_server.h"

static t_server		*init_server()
{
  t_server		*back;

  back = x_malloc(sizeof(t_server));
  back->player = NULL;
  back->team = NULL;
  back->info.max_per_team = -1;
  back->info.freq = -1;
  back->info.width = -1;
  back->info.width = -1;
  back->info.count = 0;
  return (back);
}

static t_connect        *connect_server(int port)
{
  t_connect             *back;
  struct protoent       *protocol;
  int                   a;

  a = 1;
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

static int		create_teams(t_server *server, char **name)
{
  int			a;

  a = 0;
  if ((add_team(server, GRAPHICAL_NAME)) == -1)
    return (-1);
  while (name[a] != NULL)
    {
      if ((add_team(server, name[a])) == -1)
	return (-1);
      a++;
    }
  return (0);
}

t_server		*create_server(t_opt *info)
{
  t_server		*back;

  if ((back = init_server()) == NULL)
    return (NULL);
  if ((back->connect = connect_server(info->port)) == NULL)
    {
      fprintf(stderr, "Error: Server connection failed\n");
      free(back);
      return (NULL);
    }
  back->connect->max_fd = back->connect->fd;
  if (listen(back->connect->fd, info->port) == -1)
    {
      fprintf(stderr, "Error : Listening failed\n");
      free(back);
      return (NULL);
    }
  create_teams(back, info->name_team);
  back->info.max_per_team = info->nb_client;
  back->info.freq = info->frequence;
  back->info.width = info->width;
  back->info.height = info->height;
  return (back);
}
