/*
** send.c for send in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 24 16:21:47 2017 leroy_0
** Last update Fri Jun  9 16:11:35 2017 yan
*/

#include	<string.h>
#include "myirc.h"

bool 		send_cmd(char **cmd, t_connect *client)
{
  int		x;

  x = 0;
  while (cmd && cmd[x])
    {
      if ((send(client->fd, cmd[x], strlen(cmd[x]), 0)) == -1
	  || (send(client->fd , " ", 1, 0)) == -1)
	return (false);
      x++;
    }
  if (send(client->fd, "\r\n", 2, 0) == -1)
    return (false);
  return (true);
}
