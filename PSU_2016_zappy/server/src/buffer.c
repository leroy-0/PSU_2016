/*
** buffer.c for buffer in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Fri Jun 23 13:58:04 2017 yan
** Last update Tue Jun 27 13:55:57 2017 yan
*/

#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"zappy_buffer.h"
#include	"zappy_server.h"

t_buffer	*init_buffer()
{
  t_buffer	*back;

  back = x_malloc(sizeof(t_buffer));
  bzero(back->letter, BUFFER_SIZE);
  back->start = 0;
  back->end = 0;
  return (back);
}

int			execute_buffer(t_server *server, t_player *player)
{
  char			line[BUFFER_SIZE];
  char			*command;
  int			a;

  a = 0;
  while (player->buffer->start != player->buffer->end)
    {
      line[a] = player->buffer->letter[player->buffer->start];
      a++;
      player->buffer->start = (player->buffer->start == BUFFER_SIZE - 1) ?
	0 : player->buffer->start + 1;
    }
  line[a] = '\0';
  (void)server;
  command = epur_str(strdup(line));
  printf("Command -> [%s]\n", line);
  gest_command(player, server, command);
  return (0);
}

int		read_buffer(t_server *server, t_player *player)
{
  char		buf[BUFFER_SIZE];
  ssize_t	size;
  int		pos;

  if ((size = recv(player->fd, buf, BUFFER_SIZE - 1, 0)) <= 0)
    return (1);
  buf[size] = '\0';
  pos = 0;
  while (buf[pos] != '\0')
    {
      if (buf[pos] == '\n' || buf[pos] == '\r')
	{
	  execute_buffer(server, player);
	  player->buffer->start = player->buffer->end;
	}
      else
	{
	  player->buffer->letter[player->buffer->end] = buf[pos];
	  player->buffer->end = (player->buffer->end == BUFFER_SIZE - 1) ?
	    0 : player->buffer->end + 1;
	}
      pos++;
    }
  return (0);
}
