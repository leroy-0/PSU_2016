/*
** lemipc.c for lemipc in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:42:01 2017 leroy_0
** Last update Sun Apr  2 18:42:02 2017 leroy_0
*/

#include "lemipc.h"

void            displayer(t_sdl_game *sdl, t_game *game)
{
    if (sdl->victory == false && get_victorious(game) != -1)
    {
        printf("Team number [%d] won\n", get_victorious(game) - '0');
        victory_sdl(sdl);
    }
    if (sdl->victory == true)
    {
      SDL_renderGIF(sdl->renderer, sdl->gifs);
    }
    else
      display_gameMap(sdl, game);
}

int             sdl_game(t_game *game)
{
  t_sdl_game    *sdl;

  if ((sdl = init_sdl()) == NULL)
    return (-1);

  while (!sdl->quit)
  {
    while (SDL_PollEvent(&sdl->event))
    {
      if (sdl->event.type == SDL_QUIT)
        sdl->quit = true;
      if (sdl->event.type == SDL_KEYDOWN)
        sdl->quit = true;
    }
    displayer(sdl, game);
  }

  free_sdl(sdl);
  return (0);
}

void        lemipc(char *team_key)
{
    t_game  *game;
    key_t   key;

    key = ftok(team_key, 0);
    if (!(game = init_game(key, 0, 0)))
        return ;

    while ((game->shmid = shmget(game->key, game->size, SHM_R | SHM_W)) == -1);
    game->addr = shmat(game->shmid, game->addr, SHM_R | SHM_W);
    if (game->addr == NULL)
      return ;
    if (sdl_game(game) == -1)
      return;
    if (shmdt(game->addr) == -1)
      return ;
}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        lemipc(argv[1]);
        return (0);
    }
    else
    {
        printf("Usage : %s path_to_key\n", argv[0]);
        puts("\npath_to_key [string] : valid path that will be used by ftok");
    }
    return (0);
}
