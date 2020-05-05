/*
** utils.c for  in /home/longle-h/rendu/PSU/PSU_2016_lemipc/src
** 
** Made by longle_h
** Login   <henri.longle@epitech.eu>
** 
** Started on  Sun Apr  2 13:08:56 2017 longle_h
** Last update Sun Apr  2 13:21:32 2017 longle_h
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	<stdbool.h>
#include	<stdio.h>
#include	<time.h>
#include	"lemipc.h"

char		*reverse_buf(char *src, int len)
{
  int		j;
  char		*dest;

  j = 0;
  dest = malloc(sizeof(char) * (len + 2));
  if (!dest)
    exit(EXIT_FAILURE);
  while (len >= 0)
    {
      dest[j] = src[len];
      len--;
      j++;
    }
  dest[j] = '\0';
  free(src);
  return (dest);
}

char		*createmap(unsigned int size)
{
  char		*map;
  unsigned int	x;

  x = 0;
  map = malloc(sizeof(char) * (size + 1));
  if (!map)
    exit(84);
  while (x < size)
    {
      map[x] = '0';
      x++;
    }
  map[x] = '\0';
  return (map);
}

void		print_map(t_game *game)
{
  int		i;

  i = 0;
  while (i < DEFAULT_SHMSIZE)
    {
      if (i != 0 && i % 32 == 0)
	printf("\n");
      if (game->addr[i] != '0' && game->addr[i] != '\0')
	printf("\033[31m%c\033[0m", game->addr[i]);
      else
	printf("%c", game->addr[i]);
      i++;
    }
  printf("\n");
}

int		get_next_pos(int x, int y)
{
  if (x == y)
    return (y);
  else if (x < y)
    return (y - 1);
  else if (x > y)
    return (y + 1);
  return (y);
}

bool		check_victory(t_game *game)
{
  static	int saved_time = -1;
  static	int act_time = -1;
  size_t	x;

  x = 0;
  if (saved_time == -1)
    saved_time = time(NULL);
  if (act_time < saved_time + 1)
    act_time = time(NULL);
  while (game->addr[x])
    {
      if (game->addr[x] != game->team_id + '0' && game->addr[x] != '0')
	return (false);
      x++;
    }
  if ((saved_time + 1) <= act_time && game->team_id != '0')
    return (true);
  return (false);
}
