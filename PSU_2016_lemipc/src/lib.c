/*
** lib.c for lib in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed Mar 22 08:53:32 2017 leroy_0
** Last update Sun Apr  2 13:19:05 2017 longle_h
*/

#include	<ctype.h>
#include	<stdbool.h>
#include	<string.h>
#include	"lemipc.h"

bool		is_digit(char *nb)
{
  unsigned int	x;

  x = 0;
  if (!nb)
    return (false);
  while (nb && nb[x])
    {
      if (isdigit(nb[x]) == 0)
	return (false);
      x++;
    }
  return (true);
}

bool		is_lower(char *key)
{
  if (!key || strlen(key) > 1)
    return (false);
  if (islower(key[0]) == 0)
      return (false);
  return (true);
}
