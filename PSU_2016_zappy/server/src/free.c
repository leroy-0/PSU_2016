/*
** free.c for free in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Fri Jun 23 16:15:50 2017 yan
** Last update Fri Jun 23 17:00:55 2017 yan
*/

#include	<stdlib.h>
#include	"zappy_server.h"

static void	free_teams(t_server *server)
{
  t_team	*team;
  t_team	*team_next;
  t_list_player	*player;
  t_list_player	*player_next;

  team = server->team;
  while (team)
    {
      player = team->list;
      while (player)
	{
	  player_next = player->next;
	  free(player);
	  player = player_next;
	}
      team_next = team->next;
      free(team);
      team = team_next;
    }
}

static void	free_players(t_server *server)
{
  t_player	*player;
  t_player	*next;

  player = server->player;
  while (player)
    {
      next = player->next;
      free(player->buffer);
      free(player);
      player = next;
    }
}

static void	free_tiles(t_server *server)
{
  int		y;

  y = 0;
  while (y < server->info.height)
    {
      free(server->map[y]);
      y++;
    }
  free(server->map);
}

void		free_server(t_server *server)
{
  free_teams(server);
  free_players(server);
  free_tiles(server);
}
