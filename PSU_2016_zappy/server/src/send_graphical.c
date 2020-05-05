/*
** send_graphical.c for send_graphical in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Sun Jul  2 12:34:53 2017 yan
** Last update Sun Jul  2 18:56:53 2017 yan
*/

#include	<string.h>
#include	<ctype.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"zappy_server.h"

bool		send_graphical(t_server *server, char *message)
{
  char		sent[MSG_LENGTH];
  t_list_player	*player;
  t_team	*team;

  strcpy(sent, message);
  sent[strlen(message)] = '\n';
  sent[strlen(message) + 1] = '\0';
  team = find_team(server, GRAPHICAL_NAME);
  player = team->list;
  while (player)
  {
    if (send(player->player->fd, sent, strlen(sent), 0) == -1)
      return (false);
    player = player->next;
  }
  return (true);
}

bool		send_map(t_server *server, t_player *player)
{
  char		sent[MSG_LENGTH];
  int		x;
  int		y;

  y = 0;
  while (y < server->info.height)
  {
    x = 0;
    while (x < server->info.width)
    {
      sprintf(sent, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
	      server->map[y][x].nb_ressources[0],
	      server->map[y][x].nb_ressources[1],
	      server->map[y][x].nb_ressources[2],
	      server->map[y][x].nb_ressources[3],
	      server->map[y][x].nb_ressources[4],
	      server->map[y][x].nb_ressources[5],
	      server->map[y][x].nb_ressources[6]);
      if (send(player->fd, sent, strlen(sent), 0) == -1)
	return (false);
      x++;
    }
    y++;
  }
  return (true);
}

bool		send_active_players(t_server *server, t_player *player)
{
  char		sent[MSG_LENGTH];
  t_player	*tmp;

  tmp = server->player;
  while (tmp)
  {
    sprintf(sent, "pnw %d %d %d %d %d %s\n", tmp->id, tmp->pos.x,
		   tmp->pos.y, tmp->dir, tmp->elevation, tmp->name_team);
    if (tmp->team == true && strcmp(tmp->name_team, GRAPHICAL_NAME) != 0 &&
	send(player->fd, sent, strlen(sent), 0) != 0)
      return (false);
    tmp = tmp->next;
  }
  return (true);
}

bool		send_teams(t_server *server, t_player *player)
{
  char		sent[MSG_LENGTH];
  t_team	*tmp;

  tmp = server->team;
  while (tmp)
  {
    sprintf(sent, "tna %s\n", tmp->name);
    if (send(player->fd, sent, strlen(sent), 0) == -1)
      return (false);
    tmp = tmp->next;
  }
  return (true);
}

bool		send_tile(t_server *server, int x, int y)
{
  char		msg[MSG_LENGTH];

  sprintf(msg, "bct %d %d %d %d %d %d %d %d %d", x, y,
	  server->map[y][x].nb_ressources[0],
	  server->map[y][x].nb_ressources[1],
	  server->map[y][x].nb_ressources[2],
	  server->map[y][x].nb_ressources[3],
	  server->map[y][x].nb_ressources[4],
	  server->map[y][x].nb_ressources[5],
	  server->map[y][x].nb_ressources[6]);
  if (send_graphical(server, msg) == false)
    return (false);
  return (true);
}
