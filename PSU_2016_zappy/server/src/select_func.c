/*
** select_func.c for select_func in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 17:32:51 2017 yan
** Last update Fri Jun 23 16:37:12 2017 yan
*/

#include	"zappy_server.h"

void			reset_select(t_server *server)
{
  t_player		*tmp;

  FD_ZERO(&(server->connect->fdset));
  tmp = server->player;
  FD_SET(server->connect->fd, &(server->connect->fdset));
  FD_SET(0, &(server->connect->fdset));
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &(server->connect->fdset));
      tmp = tmp->next;
    }
}

int			check_end()
{
  char			buf[BUFFER_SIZE];
  ssize_t		size;

  if ((size = read(0, buf, BUFFER_SIZE)) == -1)
    return (-1);
  buf[size] = '\0';
  if (buf[0] == 0)
    return (1);
  return (0);
}

int			analyse_select(t_server *server)
{
  t_player		*tmp;
  int			back;

  if (FD_ISSET(server->connect->fd, &(server->connect->fdset)))
    accept_new_player(server);
  tmp = server->player;
  while (tmp)
    {
      back = 0;
      if (FD_ISSET(tmp->fd, &(server->connect->fdset)))
	back = read_buffer(server, tmp);
      if (back == QUIT_PLAYER)
	tmp = remove_player(server, tmp);
      else
	tmp = tmp->next;
    }
  if (FD_ISSET(0, &(server->connect->fdset)))
    return (check_end());
  return (0);
}
