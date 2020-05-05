/*
** get_next_line.c for get_next_line in
**
** Made by leroy_0
** Login   <leroy_0@epitech.net>
**
** Started on  Thu Apr 21 09:35:55 2016 leroy_0
** Last update Thu Apr 21 10:40:04 2016 leroy_0
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int     s_len(char *str)
{
  int   i;

  i = 0;
  if (str == NULL)
    return (0);
  else
    {
      while (str[i] != '\0')
        i++;
      return (i);
    }
  return (0);
}

int		s_check_line(char *buffer, int where)
{
  while (buffer[where] != '\n' && buffer[where] != '\0')
    where++;
  if (buffer[where] == '\n')
    return (where);
  else
    return (-1);
  return (0);
}

char		*s_realloc(char **res, char *buffer, int where, int whl)
{
  char	*tmp;
  int	a;

  a = 0;
  if (whl == 0)
    {
      if ((tmp = malloc(sizeof(char) * s_len(buffer) + 2)) == NULL)
	return (NULL);
    }
  else if (whl == 1)
    {
      if ((tmp = malloc(sizeof(char)
			* (s_len(*res) + s_len(buffer) + 3))) == NULL)
	return (NULL);
      while ((*res)[a] != '\0')
	{
	  tmp[a] = (*res)[a];
	  a++;
	}
    }
  while (buffer[where])
    tmp[a++] = buffer[where++];
  tmp[a] = '\0';
  free(*res);
  return (tmp);
}

char		*s_alloc(const int fd, int r, char *buffer)
{
  static int	where = 0;
  char	*res;
  int	whl;

  whl = 0;
  if ((res = malloc(sizeof(char) * s_len(buffer) + 2)) == NULL)
    return (NULL);
  while (s_check_line(buffer, where) == -1 && r > 0)
    {
      res = s_realloc(&res, buffer, where, whl);
      where = s_check_line(buffer, where) + 1;
      whl = 1;
      if ((r = read(fd, buffer, READ_SIZE)) < 0)
	return (NULL);
      buffer[r] = '\0';
    }
  if (s_check_line(buffer, where) != -1 && r > 0)
    res = s_realloc(&res, buffer, where, whl);
  where = s_check_line(buffer, where) + 1;
  if (s_check_line(res, 0) != -1)
    res[s_check_line(res, 0)] = '\0';
  if (r == 0 && where == 0 && res[0] == '\0' && buffer[0] == '\0')
    return (NULL);
  return (res);
}

char		*get_next_line(const int fd)
{
  static char	*buffer;
  static int	alloced = 0;
  static int	r = 0;

  if (fd == -1)
    return (NULL);
  if (alloced == 0)
    {
      if ((buffer = malloc(sizeof(char) * READ_SIZE + 1)) == NULL)
	return (NULL);
      if ((r = read(fd, buffer, READ_SIZE)) < 0)
	return (NULL);
      buffer[r] = '\0';
      alloced = 1;
    }
  if (alloced == 1)
    return (s_alloc(fd, r, buffer));
  return (NULL);
}
