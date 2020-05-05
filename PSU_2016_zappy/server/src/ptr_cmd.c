/*
** ptr_cmd.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/ptr_cmd.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Fri Jun 23 12:56:49 2017 Arthur Klein
** Last update Sun Jul  2 18:59:22 2017 yan
*/

#include		<stdbool.h>
#include		<string.h>
#include		"zappy_server.h"

bool			broadcast(t_server *server, char *line, t_player *player)
{
  t_player		*tmp;
  char			*message;

  tmp = server->player;
  while (tmp)
    {
      if (tmp != player)
	{
	  message = message_to_broadcast(server, player, tmp, line);
	  send_message(tmp->fd, message);
	  free(message);
	}
      tmp = tmp->next;
    }
  send_message(player->fd, "ok");
  return (true);
}

bool			my_fork(t_server *server, char *line, t_player *player)
{
  char			msg[MSG_LENGTH];
  t_eggs		*tmp;

  tmp = player->eggs;
  (void)(server);
  (void)(line);
  (void)(player);
  if ((server->info.max_per_team
       - count_players(find_team(server, player->name_team))) > 0)
  {
    while (tmp != NULL && !tmp->activate)
      tmp = tmp->next;
    send_message(player->fd, "ok");
    sprintf(msg, "enw %d %d %d %d\n", tmp->id, player->id, player->pos.x,
	    player->pos.y);
    tmp->activate = false;
    send_graphical(server, msg);
  }
  else
    send_message(player->fd, "ko");
  return (true);
}

bool			death(t_server *server, t_player *player)
{
  printf("player %d died\n", player->id);
  send_message(player->fd, "dead");
  remove_player(server, player);
  return (false);
}

t_ptr_cmd		*init_my_ptr_func_next_cmd(t_ptr_cmd *ptr)
{
  ptr[6].ptr = &left;
  ptr[6].cmd = "Left";
  ptr[6].time = 7;
  ptr[7].ptr = &right;
  ptr[7].cmd = "Right";
  ptr[7].time = 7;
  ptr[8].ptr = &look;
  ptr[8].cmd = "Look";
  ptr[8].time = 7;
  ptr[9].ptr = &incantation;
  ptr[9].cmd = "Incantation";
  ptr[9].time = 300;
  ptr[10].ptr = &take;
  ptr[10].cmd = "Take";
  ptr[10].time = 0;
  ptr[11].ptr = &inventory;
  ptr[11].cmd = "Inventory";
  ptr[11].time = 0;
  ptr[12].ptr = &error;
  ptr[12].cmd = "Error";
  ptr[12].time = 0;
  ptr[13].ptr = NULL;
  return (ptr);
}

t_ptr_cmd		*init_my_ptr_func_cmd()
{
  t_ptr_cmd		*ptr;

  ptr = x_malloc(sizeof(t_ptr_cmd) * 14);
  ptr[0].ptr = &broadcast;
  ptr[0].cmd = "Broadcast";
  ptr[0].time = 7;
  ptr[1].ptr = &my_fork;
  ptr[1].cmd = "Fork";
  ptr[1].time = 42;
  ptr[2].ptr = &set;
  ptr[2].cmd = "Set";
  ptr[2].time = 7;
  ptr[3].ptr = &eject;
  ptr[3].cmd = "Eject";
  ptr[3].time = 7;
  ptr[4].ptr = &connect_nbr;
  ptr[4].cmd = "Connect_nbr";
  ptr[4].time = 0;
  ptr[5].ptr = &forward;
  ptr[5].cmd = "Forward";
  ptr[5].time = 7;
  ptr = init_my_ptr_func_next_cmd(ptr);
  return (ptr);
}
