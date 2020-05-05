/*
** ptr_cmd_next.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/ptr_cmd_next.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Fri Jun 23 14:37:22 2017 Arthur Klein
** Last update Sun Jul  2 22:02:31 2017 Bachelet
*/

#include	<string.h>
#include	"zappy_server.h"

bool		connect_nbr(t_server *server, char *line, t_player *player)
{
  int		unused;
  t_team 	*team;
  char		message[256];

  (void)line;
  team = find_team(server, player->name_team);
  unused = server->info.max_per_team - count_players(team);
  sprintf(message, "%d", unused);
  send_message(player->fd,  message);
  return (true);
}

bool		incantation(t_server *server, char *line, t_player *player)
{
  int		i;
  int		j;
  static int	requirement[7][7] = {{1, 1, 0, 0, 0, 0, 0},
				     {2, 1, 1, 1, 0, 0, 0},
				     {2, 2, 0, 1, 0, 2, 0},
				     {4, 1, 1, 2, 0, 1, 0},
				     {4, 1, 2, 1, 3, 0, 0},
				     {6, 1, 2, 3, 0, 1, 0},
				     {6, 2, 2, 2, 2, 2, 1}};

  i = 1;
  j = 1;
  (void)server;
  (void)line;
  if (count_nb_player(server->map[player->pos.y][player->pos.x]) !=
      requirement[player->elevation - 1][0])
    return (send_message(player->fd, "ko"));
  while (i < 7)
    if (server->map[player->pos.y][player->pos.x].nb_ressources[i++] !=
	requirement[player->elevation - 1][j])
      return (send_message(player->fd, "ko"));
    else if (j < 6)
      j++;
  make_elevation(&server->map[player->pos.y][player->pos.x], server);
  return (true);
}

bool		inventory(t_server *server, char *line, t_player *player)
{
  int           ret;
  char          *inventory;

  (void)line;
  (void)server;
  inventory = strdup("[");
  inventory = add_element_inventory(inventory, player->inventory[0], "food ");
  inventory = add_element_inventory(inventory, player->inventory[1],
				    ", linemate ");
  inventory = add_element_inventory(inventory, player->inventory[2],
				    ", deraumere ");
  inventory = add_element_inventory(inventory, player->inventory[3],
				    ", sibur ");
  inventory = add_element_inventory(inventory, player->inventory[4],
				    ", mendiane ");
  inventory = add_element_inventory(inventory, player->inventory[5],
				    ", phiras ");
  inventory = add_element_inventory(inventory, player->inventory[6],
				    ", thystame ");
  inventory = my_add_to_str(inventory, "]");
  ret = send_message(player->fd, inventory);
  free(inventory);
  return ((ret != -1) ? true : false);
}

bool		error(t_server *server, char *line, t_player *player)
{
  (void)server;
  (void)line;
  send_message(player->fd, "ko");
  return (true);
}
