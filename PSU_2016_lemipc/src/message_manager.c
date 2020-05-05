/*
** message_manager.c for  in /home/longle-h/rendu/PSU/PSU_2016_lemipc/src
** 
** Made by longle_h
** Login   <henri.longle@epitech.eu>
** 
** Started on  Sun Apr  2 12:56:16 2017 longle_h
** Last update Sun Apr  2 12:57:32 2017 longle_h
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>
#include	<sys/msg.h>
#include	"lemipc.h"

void		send_position(t_game *game, size_t pos)
{
  t_msg		mess;

  strcpy(mess.mtext, positon_to_string(pos));
  mess.mtype = game->team_id;
  msgsnd(game->mesid_team,
	 &mess, sizeof(mess.mtext), game->team_id);
}

t_pos		receive_position(t_game *game)
{
  t_msg		mess;
  t_pos		pos_map;

  pos_map.x = -1;
  pos_map.y = -1;
  if (msgrcv(game->mesid_team, &mess, sizeof(t_msg),
    game->team_id, IPC_NOWAIT) != -1)
    pos_map = pos_to_x_y((size_t)atoi(mess.mtext));
  return (pos_map);
}
