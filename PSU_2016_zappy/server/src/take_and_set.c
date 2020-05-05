/*
** take_and_set.c for take_and_set in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Sun Jul  2 13:33:38 2017 Bachelet
** Last update Sun Jul  2 13:38:17 2017 Bachelet
*/

#include	<stdbool.h>
#include	<string.h>
#include	"zappy_server.h"
#include	"zappy_player.h"

int             find_object_type(char *line)
{
  static char   *name[] = {"FOOD", "LINEMATE", "DERAUMERE", "SIBUR",
                           "MENDIANE", "PHIRAS", "THYSTAME"};
  char          object[30];
  int           a;
  char          *str;

  str = strtok(line, " ");
  strcpy(object, line + strlen(str) + 1);
  a = 0;
  while (a < 7)
    {
      if (strcasecmp(name[a], object) == 0)
	return (a);
      a++;
    }
  return (-1);
}

bool            take(t_server *server, char *line, t_player *player)
{
  int           b;
  t_pos         tmp;

  b = find_object_type(line);
  if (b == -1 ||
      server->map[player->pos.y][player->pos.x].nb_ressources[b] == 0)
    {
      send_message(player->fd, "ko");
      return (false);
    }
  tmp.x = rand() % server->info.width;
  tmp.y = rand() % server->info.height;
  server->map[player->pos.y][player->pos.x].nb_ressources[b]--;
  if (tmp.x != player->pos.x || tmp.y != player->pos.y)
    server->map[tmp.y][tmp.x].nb_ressources[b]++;
  else
    {
      tmp.x = rand() % server->info.width;
      tmp.y = rand() % server->info.height;
      server->map[tmp.y][tmp.x].nb_ressources[b]++;
    }
  player->inventory[b]++;
  send_message(player->fd, "ok");
  return (true);
}

bool            set(t_server *server, char *line, t_player *player)
{
  int           b;

  b = find_object_type(line);
  if (b == -1 || player->inventory[b] == 0)
    {
      send_message(player->fd, "ko");
      return (false);
    }
  server->map[player->pos.y][player->pos.x].nb_ressources[b]++;
  player->inventory[b]--;
  send_message(player->fd, "ok");
  return (true);
}
