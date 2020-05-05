/*
** player.c for player in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 14:51:21 2017 yan
** Last update Sun Jul  2 20:41:28 2017 leroy_0
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"zappy_player.h"
#include	"zappy_server.h"

void		init_inventory(t_player *player)
{
  int		a;

  a = LINEMATE;
  player->inventory[FOOD] = 9;
  while (a < 7)
    {
      player->inventory[a] = 0;
      a++;
    }
}

t_player	*init_player()
{
  t_player	*back;

  if ((back = malloc(sizeof(t_player))) == NULL)
    {
      fprintf(stderr, "Error: Malloc failed\n");
      return (NULL);
    }
  back->dir = UP;
  back->pos.x = -3;
  back->pos.y = -3;
  back->fd = -1;
  back->next = NULL;
  back->elevation = 1;
  back->eggs = NULL;
  back->eggs = init_eggs_list(back->eggs);
  back->team = false;
  back->buffer = init_buffer();
  back->queue = NULL;
  init_inventory(back);
  bzero(back->name_team, 256);
  return (back);
}

int		accept_new_player(t_server *server)
{
  t_player	*create;
  socklen_t	socket_size;

  socket_size = sizeof(server->connect);
  create = init_player();
  if ((create->fd = accept(server->connect->fd,
                           (struct sockaddr *)(&(server->connect->s)),
                           &(socket_size))) == -1)
    return (-1);
  create->health.life = 126 / server->info.freq;
  create->health.last = -1;
  add_player_to_server(server, create);
  update_max_fd(server);
  printf("New player accepted\n");
  send(create->fd, "WELCOME\n", strlen("WELCOME\n"), 0);
  return (0);
}

static int	team_init(t_server *server, t_list_player *create,
			     t_player *player, t_team *team)
{
  t_list_player	*tmp;
  char		msg[MSG_LENGTH];

  tmp = team->list;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp == NULL)
    team->list = create;
  else
    tmp->next = create;
  player->pos.y = rand() % server->info.height;
  player->pos.x = rand() % server->info.width;
  if (server->map[player->pos.y][player->pos.x].player_list == NULL)
    add_list_player(&(server->map[player->pos.y][player->pos.x].player_list),
		    create_list_player(player));
  sprintf(msg, "%d\n%d %d", server->info.max_per_team - count_players(team),
	  server->info.width, server->info.height);
  send_message(player->fd, msg);
  sprintf(msg, "pnw %d %d %d %d %d %s", player->id, player->pos.x,
	  player->pos.y, player->dir, player->elevation, player->name_team);
  if (send_graphical(server, msg) == false)
    return (-1);
  return (0);
}

int		add_player_to_team(t_server *server, char *team_name,
				   t_player *player)
{
  t_team	*team;
  t_list_player	*create;

  if (strcmp(GRAPHICAL_NAME, team_name) == 0)
    return (add_graphical(server, player));
  if ((team = find_team(server, team_name)) == NULL ||
      (count_players(team) >= server->info.max_per_team))
  {
    send_message(player->fd, "ko");
    return (1);
  }
  if ((create = create_list_player(player)) == NULL)
    return (-1);
  player->team = true;
  strcpy(player->name_team, team_name);
  return (team_init(server, create, player, team));
}
