/*
** player.c for player in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 14:51:21 2017 yan
** Last update Sun Jul  2 18:23:37 2017 yan
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"zappy_player.h"
#include	"zappy_server.h"

int		add_graphical(t_server *server, t_player *player)
{
  t_team	*team;
  t_list_player	*tmp;
  t_list_player	*create;
  char		msg[MSG_LENGTH];

  team = find_team(server, GRAPHICAL_NAME);
  if ((create = create_list_player(player)) == NULL)
    return (-1);
  tmp = team->list;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp == NULL)
    team->list = create;
  else
    tmp->next = create;
  player->team = true;
  strcpy(player->name_team, GRAPHICAL_NAME);
  sprintf(msg, "msz %d %d\nsgt %d", server->info.width, server->info.height,
	  server->info.freq);
  send_message(player->fd, msg);
  send_map(server, player);
  send_teams(server, player);
  send_active_players(server, player);
  return (0);
}

void		add_player_to_server(t_server *server, t_player *player)
{
  t_player	*tmp;

  tmp = server->player;
  player->id = server->info.count;
  printf("new player with id %d\n", player->id);
  server->info.count++;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp == NULL)
    server->player = player;
  else
    tmp->next = player;
}

void		remove_from_tile(t_server *server, t_player *player)
{
  t_list_player	*tmp;
  t_list_player	*before;
  t_tile	*tile;

  if (player->pos.y >= 0 && player->pos.x >= 0)
    {
      tile = &server->map[player->pos.y][player->pos.x];
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
	}
    }
}

void		delete_from_team(t_server *server, t_list_player *before,
				 t_team *team, int *status)
{
  char		msg[MSG_LENGTH];
  t_list_player	*tmp;

  tmp = (before == NULL) ? team->list : before->next;
  if (tmp != NULL)
    {
      printf("leaving team %s\n", team->name);
      sprintf(msg, "pdi %d", tmp->player->id);
      send_graphical(server, msg);
      *status = 1;
      if (team->list == tmp)
	team->list = tmp->next;
      else
	before->next = tmp->next;
      free(tmp);
    }
}

void			remove_player_from_team(t_server *server, t_player *player)
{
  t_team		*team;
  t_list_player	*before;
  t_list_player	*tmp;
  int			status;

  team = server->team;
  status = 0;
  while (team && status == 0)
    {
      tmp = team->list;
      before = NULL;
      while (tmp && tmp->player != player)
	{
	  before = tmp;
	  tmp = tmp->next;
	}
      delete_from_team(server, before, team, &status);
      team = team->next;
    }
}

  t_player	*remove_player(t_server *server, t_player *player)
  {
    t_player	*tmp;
    t_player	*before;
    t_player	*next;

    if (player->team == true)
      {
	remove_player_from_team(server, player);
	remove_from_tile(server, player);
      }
    next = player->next;
    tmp = server->player;
    before = NULL;
    while (tmp && tmp != player)
      {
	before = tmp;
	tmp = tmp->next;
      }
    if (tmp != NULL)
      {
	if (before == NULL)
	  server->player = tmp->next;
	else
	  before->next = tmp->next;
	printf("player %d disconnected\n", player->id);
	close(tmp->fd);
	free(tmp->buffer);
	free(tmp);
      }
    return (next);
  }
