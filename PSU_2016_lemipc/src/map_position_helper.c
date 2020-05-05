/*
** map_position_helper.c for  in /home/longle-h/rendu/PSU/PSU_2016_lemipc/src
** 
** Made by longle_h
** Login   <henri.longle@epitech.eu>
** 
** Started on  Sun Apr  2 13:05:08 2017 longle_h
** Last update Sun Apr  2 13:08:37 2017 longle_h
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"lemipc.h"

char		*positon_to_string(size_t pos)
{
  int		mod;
  char		*buf;
  int		i;

  i = 0;
  buf = malloc(sizeof(char) * (MAXLENMSG + 1));
  if (!buf)
    exit(EXIT_FAILURE);
  while (pos >= 10)
    {
      mod = (pos % 10);
      pos = (pos - mod) / 10;
      buf[i] = (mod + '0');
      i++;
    }
  buf[i] = ((pos % 10) + '0');
  return (reverse_buf(buf, i));
}

t_pos		pos_to_x_y(size_t player_pos)
{
  t_pos		result;

  if (player_pos > DEFAULT_SHMSIZE)
    exit(84);
  result.y = player_pos / 32;
  result.x = player_pos % 32;
  return (result);
}

e_where		getDir(int x, int y, int x2, int y2)
{
  if (x2 > x)
    {
      if (y2 < y)
	return (UP_R);
      else if (y2 == y)
	return (RIGHT);
      else if (y2 > y)
	return (DOWN_R);
    }
  else
    {
      if (y2 < y)
	return (UP_L);
      else if (y2 == y)
	return (LEFT);
      else if (y2 > y)
	return (DOWN_L);
    }
  return (UNDEFINED);
}

void		go_to_dir(t_game *game, int x, int y)
{
  t_pos		player;
  t_enemy	*cell;

  player = pos_to_x_y(game->pos_player);
  player.x = get_next_pos(x, player.x);
  player.y = get_next_pos(y, player.y);
  if (set_position(game, (player.y * 32) + player.x, game->team_id) == false)
    {
      if ((cell = malloc(sizeof(t_enemy))) == NULL)
	exit(EXIT_FAILURE);
      cell->pos = (player.y * 32) + player.x;
      cell->dir = getDir(pos_to_x_y(game->pos_player).x,
        pos_to_x_y(game->pos_player).y, x, y);
      player = attack_enemy(game, cell);
      set_position(game, (player.y * 32) + player.x, game->team_id);
    }
}
