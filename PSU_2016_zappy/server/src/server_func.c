/*
** server_func.c for server_func.c in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 15:11:04 2017 yan
** Last update Fri Jun 23 16:16:01 2017 yan
*/

#include	<stdio.h>
#include	<string.h>
#include	"zappy_server.h"

void		update_max_fd(t_server *server)
{
  int		back;
  t_player	*tmp;

  back = server->connect->fd;
  if (server->player != NULL)
    {
      tmp = server->player;
      while (tmp != NULL)
	{
	  if (tmp->fd > back)
	    back = tmp->fd;
	  tmp = tmp->next;
	}
    }
  server->connect->max_fd = back + 1;
}
