/*
** broadcast.c for broadcast in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on Tue Jun 27 15:25:53 2017 Bachelet
** Last update Sun Jul  2 20:44:10 2017 leroy_0
*/

#include	<string.h>
#include	<unistd.h>
#include	"zappy_server.h"
#include	"zappy_player.h"

t_pos		find_shortest_path(t_pos start, t_pos end, t_info info_map)
{
  t_pos		shortest_path;

  shortest_path.x = start.x - end.x;
  shortest_path.y = start.y - end.y;
  if (shortest_path.x > (info_map.width + 1) / 2)
    shortest_path.x -= info_map.width;
  else if (shortest_path.x < ((info_map.width + 1) / 2) * -1)
    shortest_path.x += info_map.width;
  if (shortest_path.y > (info_map.height + 1) / 2)
    shortest_path.y -= info_map.height;
  else if (shortest_path.y < ((info_map.height + 1) / 2) * -1)
    shortest_path.y += info_map.height;
  return (shortest_path);
}

char		get_normal_tile(t_pos path, t_player *player)
{
  double	angle;

  angle = (double)path.x / (double)path.y;
  if (angle <= 0.5 && angle > -0.5 && path.y < 0)
    return (get_tile_top(player));
  else if (angle <= 0.5 && angle > -0.5 && path.y > 0)
    return (get_tile_bottom(player));
  else if (angle <= 2.0 && angle > 0.5 && path.y < 0)
    return (get_tile_top_left(player));
  else if (angle <= -0.5 && angle > -2.0 && path.y < 0)
    return (get_tile_top_right(player));
  else if (angle <= 2.0 && angle > 0.5 && path.y > 0)
    return (get_tile_bottom_right(player));
  else if (angle <= -0.5 && angle > -2.0 && path.y > 0)
    return (get_tile_bottom_left(player));
  else if ((angle > 2.0 && path.y > 0) || (angle < -2.0 && path.y < 0))
    return (get_tile_right(player));
  else
    return (get_tile_left(player));
}

char		get_special_tile(t_pos path, t_player *player)
{
  if (path.x == 0 && path.y > 0)
    return (get_tile_bottom(player));
  else if (path.x == 0 && path.y < 0)
    return (get_tile_top(player));
  else if (path.y == 0 && path.x > 0)
    return (get_tile_right(player));
  else if (path.y == 0 && path.x < 0)
    return (get_tile_left(player));
  return ('0');
}

char		*find_matching_tile(t_pos path, t_player *player)
{
  char		*matching_tile;

  if (!(matching_tile = malloc(sizeof(char) * 3)))
    return (NULL);
  if (path.x != 0 && path.y != 0)
    matching_tile[0] = get_normal_tile(path, player);
  else
    matching_tile[0] = get_special_tile(path, player);
  matching_tile[1] = ',';
  matching_tile[2] = '\0';
  return (matching_tile);
}

char		*message_to_broadcast(t_server *server, t_player *player,
					  t_player *tmp, char *line)
{
  t_pos		shortest_path;
  char		*match_tile;
  char		*message;
  char		msg[MSG_LENGTH];

  message = NULL;
  if (!(message = my_add_to_str(message, "message ")))
    return (NULL);
  shortest_path = find_shortest_path(player->pos, tmp->pos, server->info);
  match_tile = find_matching_tile(shortest_path, tmp);
  if (!(message = my_add_to_str(message, match_tile)))
    return (NULL);
  if (!(message = my_add_to_str(message, &line[strlen("broadcast")])))
    return (NULL);
  sprintf(msg, "pbc %d %s", player->id, message);
  if (send_graphical(server, msg) == false)
    return (false);
  return (message);
}
