/*
** display.c for display in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:44:22 2017 leroy_0
** Last update Sun Apr  2 18:44:23 2017 leroy_0
*/

#include "lemipc.h"

int             victory_sdl(t_sdl_game  *sdl)
{
  if (load_music(sdl, WIN_SOUND) == false)
    return (-1);
  sdl->victory = true;
  return (0);
}

t_sdl_game      *init_sdl()
{
  t_sdl_game    *sdl;

  if (!(sdl = malloc(sizeof(t_sdl_game))))
    return (NULL);
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    return (NULL);
  sdl->pWindow = SDL_CreateWindow("Lemipc", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    1080,
    920,
    SDL_WINDOW_SHOWN);
  if (!sdl->pWindow)
    return (NULL);
  sdl->renderer = SDL_CreateRenderer(sdl->pWindow, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!sdl->renderer)
    return (NULL);
  sdl->music = NULL;
  if (load_music(sdl, AMBIENT_SOUND) == false)
    return (NULL);
  if ((sdl->gifs = SDL_LoadGIF(WIN_GIF)) == NULL)
    return (NULL);
  sdl->quit = false;
  sdl->victory = false;
  return (sdl);
}

void            free_sdl(t_sdl_game *sdl)
{
  int           x;

  x = 0;
  while (sdl->gifs[x])
  {
    SDL_FreeSurface(sdl->gifs[x]);
    x++;
  }
  Mix_FreeMusic(sdl->music);
  Mix_CloseAudio();
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->pWindow);
  SDL_Quit();
}

void            display_gameMap(t_sdl_game *sdl, t_game *game)
{
  int           x;
  int           y;

  x = 0;
  y = 0;
  SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
  SDL_RenderClear(sdl->renderer);
  while (game->addr && game->addr[x] != '\0')
  {
    if (x != 0 && x % 32 == 0)
      y++;

    if (game->addr[x] != '\0' && game->addr[x] > '0')
      filledCircleColor(sdl->renderer, ((x % 32) + 1.2) * 32,
        (y + 1) * 28, 13, rand_color(game->addr[x] - '0'));
    x++;
  }
  SDL_RenderPresent(sdl->renderer);
}

int             get_victorious(t_game *game)
{
    int         team_id;
    int         x;

    x = 0;
    team_id = -1;
    while (game->addr[x])
    {
        if (team_id != -1 && game->addr[x] != '0' && team_id != game->addr[x])
        {
            team_id = -1;
            break;
        }
        if (game->addr[x] != '0')
            team_id = game->addr[x];
        x++;
    }
    return (team_id);
}
