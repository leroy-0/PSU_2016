/*
** tools.c for tools in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Jun  1 15:30:40 2017 leroy_0
** Last update Thu Jun  1 15:30:40 2017 leroy_0
*/

#include "graphical.h"

int         rand_color(int x)
{
  int   color;

  if (x == 1)
    color = (0x0000ff);
  else if (x == 2)
    color = (0x00ff00);
  else if (x == 3)
    color = (0xff0000);
  else if (x == 4)
    color = (0xffff00);
  else
    color = (0xffffff);
  color |= (0xff) << 24;
  return (color);
}

int cstring_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return (strcmp(*ia, *ib));
}

void            free_imgs(char **imgs)
{
  int           x;

  x = 0;
  while (imgs[x])
  {
    free(imgs[x]);
    x++;
  }
  free(imgs);
}

bool            load_music(t_sdl_game *sdl, char *directory)
{
  Mix_FreeMusic(sdl->music);

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    return (false);

  sdl->music = Mix_LoadMUS(directory);
  if (sdl->music == NULL)
    return (false);

  if (Mix_PlayMusic(sdl->music, 1) == -1)
    return (false);
  return (true);
}

void            blit_background(t_sdl_game *sdl)
{
  SDL_Rect      location;

  location.x = sdl->background->w / 2 - WINSIZE_X / 2;
  location.y = sdl->background->h / 2 - WINSIZE_Y / 2;
  location.w = WINSIZE_X;
  location.h = WINSIZE_Y;

  SDL_BlitSurface(sdl->background, &location, sdl->screen, NULL);
}