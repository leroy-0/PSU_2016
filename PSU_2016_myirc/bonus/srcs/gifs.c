/*
** gifs.c for gifs in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Jun  1 15:30:34 2017 leroy_0
** Last update Thu Jun  1 15:30:34 2017 leroy_0
*/

#include "graphical.h"

char            **create_imgs(char *directory, DIR *dp,
  struct dirent *ep, int x)
{
  char          **imgs;

  if (!(imgs = malloc(sizeof(char *) * (x + 1))))
    return (NULL);
  x = 0;
  if ((dp = opendir (directory)) != NULL)
  {
    while ((ep = readdir (dp)))
    {
      if (ep->d_name[0] != '.')
      {
        imgs[x] = malloc(sizeof(char) *
          (strlen(directory) + strlen(ep->d_name) + 1));
        if (!imgs[x])
          return (NULL);
        imgs[x] = strcpy(imgs[x], directory);
        imgs[x] = strcat(imgs[x], ep->d_name);
        x++;
      }
    }
    closedir (dp);
  }
  imgs[x] = NULL;
  qsort(imgs, x, sizeof(char *), cstring_cmp);
  return (imgs);
}

char            **read_imgs(char *directory)
{
  DIR           *dp;
  struct dirent *ep;
  int           x;

  x = 0;
  dp = opendir (directory);
  if (dp != NULL)
  {
    while ((ep = readdir (dp)))
    {
      if (ep->d_name[0] != '.')
        x++;
    }
    closedir (dp);
  }
  return (create_imgs(directory, dp, ep, x));
}

SDL_Surface     **SDL_LoadGIF(char *directory)
{
  SDL_Surface   **gifs;
  char          **imgs;
  int           x;

  x = 0;
  imgs = read_imgs(directory);
  while (imgs[x])
    x++;
  gifs = malloc(sizeof(SDL_Surface) * (x + 1));
  if (!gifs)
    return (NULL);
  x = 0;
  while (imgs[x])
  {
    gifs[x] = IMG_Load(imgs[x]);
    if (!gifs[x])
    {
      printf("FAILED TO LOAD FILE=%s\n", imgs[x]);
      return (NULL);
    }
    x++;
  }
  gifs[x] = NULL;
  free_imgs(imgs);
  return (gifs);
}

int               get_increment(SDL_Surface   **gifs)
{
  static clock_t  act_time = -1;
  static int      increment = -1;
  clock_t         new_time;

  new_time = clock() / (CLOCKS_PER_SEC / 1000);
  if (act_time == -1)
  {
    act_time = clock() / (CLOCKS_PER_SEC / 1000);
    increment = 0;
  }
  if (new_time >= act_time + GIF_LATENCY)
  {
    increment++;
    act_time = new_time;
    if (gifs[increment] == NULL)
      increment = 0;
  }
  return (increment);
}

void            SDL_renderGIF(SDL_Renderer  *renderer, SDL_Surface **gifs)
{
  SDL_Texture   *texture;
  int           increment;

  increment = get_increment(gifs);
  texture = SDL_CreateTextureFromSurface(renderer, gifs[increment]);
  if (!renderer || !texture)
  {
    printf("Failed to display the gif.\n");
    return ;
  }
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(texture);
}
