/*
** game_init.c for  in /home/longle-h/rendu/PSU/PSU_2016_lemipc/src
** 
** Made by longle_h
** Login   <henri.longle@epitech.eu>
** 
** Started on  Sun Apr  2 12:51:21 2017 longle_h
** Last update Sun Apr  2 13:20:46 2017 longle_h
*/

#include	<sys/ipc.h>
#include	<sys/msg.h>
#include	<sys/sem.h>
#include	<sys/shm.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"lemipc.h"

void		game_loop(t_game *game, t_pos aim)
{
  sleep(1);
  while (420)
    {
      aim = receive_position(game);
      if (is_alive(game) == false || check_victory(game) == true)
	break;
      if ((aim.x == -1 && aim.y == -1)
	  || ((search_enemy(game, ((aim.y * 32) - 1) + aim.x,
      game->team_id + '0') == NULL)))
	aim = set_aim(game);
      else
	go_to_dir(game, aim.x, aim.y);
      send_position(game, (size_t)((32 * aim.y) + (aim.x)));
    }
  game->addr[game->pos_player] = '0';
}

bool		isalone(t_game *game)
{
  size_t	x;

  x = 0;
  while (game->addr[x])
    {
      if (x != game->pos_player && game->addr[x] == game->team_id + '0')
	return (false);
      x++;
    }
  return (true);
}

t_pos		set_aim(t_game *game)
{
  t_pos		result;
  t_enemy	*enemy;

  enemy = search_enemy(game, game->pos_player, game->team_id + '0');
  if (enemy != NULL && isalone(game) == false)
    {
      result = attack_enemy(game, enemy);
      set_position(game, result.y * 32 + result.x, game->team_id);
      result = pos_to_x_y(enemy->pos);
    }
  else
    {
      result = pos_to_x_y(DEFAULT_SHMSIZE / 2 + 16);
      go_to_dir(game, result.x, result.y);
    }
  return (result);
}

void		join_team(t_game *game)
{
  t_pos		pos_map;

  game->mesid_team = msgget(game->team_channel, 0766 | IPC_CREAT);
  if (game->mesid_team == -1)
    exit(EXIT_FAILURE);
  pos_map = receive_position(game);
  if (pos_map.x == -1 && pos_map.y == -1)
    {
      send_position(game, game->pos_player);
      pos_map = pos_to_x_y(game->pos_player);
    }
  game_loop(game, pos_map);
}

void		end_game(t_game *game)
{
  if (isalone(game) == true && check_victory(game) == true)
    {
      semctl(game->semid, 0, IPC_RMID, NULL);
      msgctl(game->mesid_team, IPC_RMID, NULL);
      shmctl(game->shmid, IPC_RMID, NULL);
    }
  if (shmdt(game->addr) == -1)
    exit(84);
}
