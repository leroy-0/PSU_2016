/*
** tools.c for tools in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:45:53 2017 leroy_0
** Last update Sun Apr  2 18:46:01 2017 leroy_0
*/

#include "lemipc.h"

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

  if (Mix_PlayMusic(sdl->music, -1) == -1)
    return (false);
  return (true);
}
