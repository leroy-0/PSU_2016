/*
** receive.c for receive in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Jun  9 17:59:12 2017 leroy_0
** Last update Fri Jun  9 17:59:12 2017 leroy_0
*/

#include	"fnc_ptrs.h"
#include  "myirc.h"
#include  "receive.h"

int             close_client(t_connect **client)
{
  char		*message[] = {"/quit", NULL};

  cmd_quit(message, client);
  return (SUCCESS);
}

t_connect   *create_client(in_addr_t ip, int port)
{
  t_connect *back;
  int   real_t;

  real_t = time(NULL);
  if ((back = init_client(ip, port)) == NULL)
    {
      fprintf(stderr, "Error : Connection failed\n");
      return (NULL);
    }
  while (connect(back->fd, (struct sockaddr *)&back->s,
     sizeof(back->s)) == -1)
    {
      if ((time(NULL) - real_t) >= TIMEOUT)
	return (false);
    }
  pthread_create(&back->reader, NULL, read_stdin, back);
  return (back);
}

void		     *read_stdin(void *param)
{
  t_connect *client;
  char		  *msg;
  char		  *buf;
  int		    r;

  client = (t_connect *)param;
  if ((buf = malloc(sizeof(char) * MAX_PATH)) == NULL)
    return (NULL);
  while (42)
    {
      if (!client || (r = recv(client->fd, buf, MAX_PATH, 0)) == -1)
	{
	  free(client);
	  return (NULL);
	}
      buf[r] = '\0';
      if ((msg = epur_string(buf)))
      {
        printf("%s\n", msg);
        free(msg);
      }
      if ((buf = malloc(sizeof(char) * MAX_PATH)) == NULL)
        return (NULL);
    }
  return (NULL);
}
