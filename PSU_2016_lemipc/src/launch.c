/*
** launch.c for launch in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Tue Mar 28 23:26:27 2017 leroy_0
** Last update Sun Apr  2 13:22:08 2017 longle_h
*/

#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<sys/sem.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"lemipc.h"

t_game		*init_game(key_t key, int id, key_t team_channel)
{
  t_game	*game;

  if (!(game = malloc(sizeof(t_game))))
    return (NULL);
  game->key = key;
  game->team_id = id;
  game->team_channel = team_channel;
  game->size = (size_t)DEFAULT_SHMSIZE;
  game->shmflg = IPC_CREAT | SHM_R | SHM_W;
  game->shmid = -1;
  game->addr = NULL;
  return (game);
}

void		first_player(t_game *game)
{
  game->semid = semget(game->key, 1, game->shmflg);
  if (game->semid == -1)
    exit(EXIT_FAILURE);
  game->shmid = shmget(game->key, game->size, game->shmflg);
  if (game->shmid == -1)
    exit(EXIT_FAILURE);
  game->addr = shmat(game->shmid, game->addr, SHM_R | SHM_W);
  if (!game->addr)
    exit(EXIT_FAILURE);
  sprintf(game->addr, createmap(game->size));
  if (semctl(game->semid, 0, SETVAL, 1) == -1)
    exit(EXIT_FAILURE);
}

void		other_player(t_game *game)
{
  game->addr = shmat(game->shmid, game->addr, SHM_R | SHM_W);
  if (game->addr == NULL)
    exit(EXIT_FAILURE);
  game->semid = semget(game->key, 1, SHM_R | SHM_W);
  if (game->semid == -1)
    exit(EXIT_FAILURE);
}

bool		set_position(t_game *game, size_t pos, int team_id)
{
  if (pos >= DEFAULT_SHMSIZE)
    exit(EXIT_FAILURE);
  if (game->addr[pos] != '\0' && game->addr[pos] == '0')
    {
      lock(game);
      game->addr[pos] = (team_id + '0');
      game->addr[game->pos_player] = '0';
      game->pos_player = pos;
      unlock(game);
      return (true);
    }
  return (false);
}

void		launch_game(t_game *game)
{
  size_t	pos;

  pos = rand() % game->size;
  while (game->addr[pos] != '0')
    pos = rand() % game->size;
  game->addr[pos] = (game->team_id + '0');
  game->pos_player = pos;
  join_team(game);
  end_game(game);
}
