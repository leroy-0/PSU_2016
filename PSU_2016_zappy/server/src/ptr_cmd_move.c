/*
** ptr_cmd_move.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/ptr_cmd_move.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Fri Jun 23 14:37:54 2017 Arthur Klein
** Last update Sun Jul  2 17:48:49 2017 yan
*/

#include		<stdbool.h>
#include		"zappy_server.h"

void			update_on_map(t_server *server, t_player *player, t_pos pos)
{
  t_tile		*tile;
  t_tile		*new_tile;
  t_list_player		*tmp;
  t_list_player		*before;

  tile = &server->map[player->pos.y][player->pos.x];
  new_tile = &server->map[pos.y][pos.x];
  tmp = tile->player_list;
  before = NULL;
  while (tmp && tmp->player != player)
    {
      before = tmp;
      tmp = tmp->next;
    }
  if (tmp != NULL)
    {
      if (before == NULL)
	tile->player_list = tmp->next;
      else
	before->next = tmp->next;
      add_list_player(&new_tile->player_list, tmp);
    }
}

bool			forward(t_server *server, char *line, t_player *player)
{
  bool           	ret;
  t_pos			new_pos;
  char			msg[MSG_LENGTH];

  (void)line;
  new_pos.x = player->pos.x;
  new_pos.y = player->pos.y;
  update_new_pos(player->dir, &new_pos, server->info);
  update_on_map(server, player, new_pos);
  set_position(server, player, new_pos.x, new_pos.y);
  sprintf(msg, "ppo %d %d %d %d", player->id, player->pos.x,
	  player->pos.y, player->dir);
  if (send_graphical(server, msg) == false)
    return (false);
  ret = send_message(player->fd, "ok");
  return (ret);
}

bool			left(t_server *server, char *line, t_player *player)
{
  bool           	ret;
  char			msg[MSG_LENGTH];

  (void)server;
  (void)line;
  if (player->dir == UP)
    player->dir = LEFT;
  else if (player->dir == RIGHT)
    player->dir = UP;
  else if (player->dir == LEFT)
    player->dir = DOWN;
  else
    player->dir = RIGHT;
  sprintf(msg, "ppo %d %d %d %d", player->id, player->pos.x,
	  player->pos.y, player->dir);
  if (send_graphical(server, msg) == false)
    return (false);
  ret = send_message(player->fd, "ok");
  return (ret);
}

bool			right(t_server *server, char *line, t_player *player)
{
  bool			ret;
  char			msg[MSG_LENGTH];

  (void)server;
  (void)line;
  if (player->dir == UP)
    player->dir = RIGHT;
  else if (player->dir == RIGHT)
    player->dir = DOWN;
  else if (player->dir == LEFT)
    player->dir = UP;
  else
    player->dir = LEFT;
  sprintf(msg, "ppo %d %d %d %d", player->id, player->pos.x,
	  player->pos.y, player->dir);
  if (send_graphical(server, msg) == false)
    return (false);
  ret = send_message(player->fd, "ok");
  return (ret);
}

bool			look(t_server *server, char *line, t_player *player)
{
  int           ret;
  char          *looked;

  (void)line;
  if (player->dir == UP)
    looked = look_top(player, server);
  else if (player->dir == RIGHT)
    looked = look_right(player, server);
  else if (player->dir == LEFT)
    looked = look_left(player, server);
  else
    looked = look_bottom(player, server);
  ret = send_message(player->fd, looked);
  free(looked);
  return (ret);
}
