/*
** display.c for display in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Jun  1 15:30:26 2017 leroy_0
** Last update Thu Jun  1 15:30:26 2017 leroy_0
*/

#include "graphical.h"

t_chat        *init_chat()
{
  t_chat      *new;

  new = malloc(sizeof(t_chat));
  new->hist = 0;
  new->channel = NULL;
  new->msgs = malloc(sizeof(char *) * MAX_MSG);
  new->next = NULL;
  return (new);
}

void            init_msg(t_sdl_game *sdl)
{
  if (!(sdl->msg = malloc(sizeof(char) * MAX_MSG)))
    return ;
  sdl->msg[0] = '\0';
  sdl->msg = strcat(sdl->msg, sdl->username);
  sdl->msg_len = 0;
}

t_sdl_game      *init_all()
{
  t_sdl_game    *sdl;

  if ((sdl = init_sdl()) == NULL)
    return (NULL);

  if ((sdl->gifs = SDL_LoadGIF(WIN_GIF)) == NULL)
    return (NULL);

  sdl->username = "";
  sdl->modif = true;
  sdl->finished = true;
  sdl->client = NULL;

  sdl->chat = init_chat();
  init_msg(sdl);
  blit_background(sdl);
  return (sdl);
}

t_sdl_game      *init_sdl()
{
  t_sdl_game    *sdl;

  if (!(sdl = malloc(sizeof(t_sdl_game))))
    return (NULL);
  if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
    return (NULL);
  sdl->pWindow = SDL_CreateWindow("MY_IRC", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WINSIZE_X,
    WINSIZE_Y,
    SDL_WINDOW_SHOWN);
  if (!sdl->pWindow)
    return (NULL);
  sdl->renderer = SDL_CreateRenderer(sdl->pWindow, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!sdl->renderer)
    return (NULL);
  sdl->screen = SDL_GetWindowSurface(sdl->pWindow);
  sdl->background = IMG_Load(DEFAULT_BACKGROUND);
  sdl->channel = IMG_Load(DEFAULT_BOX);
  sdl->font = TTF_OpenFont(DEFAULT_POLICE, SIZE_FONT);
  sdl->music = NULL;
  sdl->quit = false;
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
  free(sdl->msg);
  free(sdl->chat);
  Mix_FreeMusic(sdl->music);
  Mix_CloseAudio();
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->pWindow);
  SDL_StopTextInput();
  TTF_CloseFont(sdl->font);
  SDL_Quit();
}
