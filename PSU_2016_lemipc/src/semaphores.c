/*
** semaphores.c for semaphores in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 17:57:31 2017 leroy_0
** Last update Sun Apr  2 17:57:31 2017 leroy_0
*/

#include  <sys/sem.h>
#include "lemipc.h"

void		lock(t_game *game)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = -1;
  semop(game->semid, &sops, 1);
}

void		unlock(t_game *game)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = 1;
  semop(game->semid, &sops, 1);
}
