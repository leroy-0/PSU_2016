/*
** client.c for client in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:21:04 2017 leroy_0
** Last update Fri Jun  9 16:30:41 2017 yan
*/

#include		<netdb.h>
#include 		<time.h>
#include		<pthread.h>
#include		"myirc.h"
#include 		"fnc_ptrs.h"

t_connect		*init_client(in_addr_t ip, int port)
{
  t_connect		*back;
  struct protoent	*protocol;

  if ((back = malloc(sizeof(t_connect))) == NULL)
    return (NULL);
  back->s.sin_family = AF_INET;
  back->s.sin_addr.s_addr = ip;
  back->s.sin_port = port;
  if ((protocol = getprotobyname("TCP")) == NULL ||
      ((back->fd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1))
    {
      free(back);
      return (NULL);
    }
  return (back);
}

int			run_client(t_connect *client)
{
  char			*err;
  char			*buffer;
  size_t		size;
  int			ret;

  size = MAX_PATH;
  if ((buffer = malloc(sizeof(char) * size)) == NULL)
    return (FATAL_ERROR);
  while (getline(&buffer, &size, stdin) != -1)
    {
      if (check_validity(&buffer))
	{
	  ret = manage_commands(buffer, &client);
	  if ((err = get_error(ret)))
	    printf("%s\n", err);
	  if (ret == FATAL_ERROR || ret == EXIT)
	    return (FATAL_ERROR);
	}
      else
	printf("%s\n", get_error(BAD_COMMAND));
      if (!(buffer = malloc(sizeof(char) * MAX_PATH)))
	return (FATAL_ERROR);
    }
  return (0);
}

int			start_client()
{
  t_connect		*client;

  client = NULL;
  if (run_client(client) == -1)
    return (-1);
  if (client && close(client->fd) == -1)
    {
      fprintf(stderr, "Error : Close\n");
      return (1);
    }
  if (client)
    free(client);
  return (0);
}
