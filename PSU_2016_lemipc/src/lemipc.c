/*
** lemipc.c for lemipc in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 17:56:52 2017 leroy_0
** Last update Sun Apr  2 17:56:53 2017 leroy_0
*/

#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<stdio.h>
#include	<time.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"lemipc.h"

void		lemipc(char *team_key, int team_lvl)
{
  t_game	*game;
  key_t		team_channel;
  key_t		key;

  key = ftok(team_key, 0);
  team_channel = ftok(team_key, team_lvl);
  if (!(game = init_game(key, team_lvl, team_channel)))
    exit(84);
  if ((game->shmid = shmget(game->key, game->size, SHM_R | SHM_W)) == -1)
    first_player(game);
  else
    other_player(game);
  launch_game(game);
}

int		main(int argc, char **argv)
{
  srand(time(NULL) * getpid());
  if (argc == 3)
    {
      if (is_digit(argv[2]) == true)
	{
	  lemipc(argv[1], atoi(argv[2]));
	  return (0);
	}
      printf("Arguments are not valid. Launch without args for help\n");
    }
  else
    {
      printf("Usage : %s path_to_key team_number\n", argv[0]);
      puts("\npath_to_key [string] : valid path that will be used by ftok");
      puts("team_number [0+] : team number assigned to the current player");
    }
  return (0);
}
