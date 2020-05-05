/*
** tools2.c for tools2 in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Jun  9 18:21:53 2017 leroy_0
** Last update Fri Jun  9 18:21:53 2017 leroy_0
*/

#include 	<ctype.h>
#include	<string.h>
#include 	"common.h"

bool		check_connection(char *line, char **ip, char **port)
{
  int		a;

  a = 0;
  while (line[a] != '\0' && line[a] != ':')
    a++;
  if (line[a] == '\0' ||
      (*ip = malloc(sizeof(char) * (a + 1))) == NULL ||
      (*port = malloc(sizeof(char) * (1 + strlen(line) - a))) == NULL)
    return (false);
  if (strncpy(*ip, line, a) == NULL ||
      strncpy(*port, line + a + 1, strlen(line) - a) == NULL)
    return (false);
  (*ip)[a] = '\0';
  (*port)[strlen(line) - a] = '\0';
  if (is_ip(*ip) == false || is_digit(*port) == false)
    return (false);
  return (true);
}

bool		is_ip(const char *ip)
{
  int		count;
  int		x;

  x = 0;
  count = 0;
  while (ip && ip[x])
    {
      if (isdigit(ip[x]))
	x++;
      else
	{
	  if (ip[x] == ',' || ip[x] == '.')
	    {
	      count++;
	      x++;
	    }
	  else
	    break;
	}
    }
  if (count == 3 && isdigit(ip[strlen(ip) - 1]))
    return (true);
  return (false);
}

bool 		is_digit(const char *nb)
{
  int		x;

  x = 0;
  if (!nb)
    return (false);
  while (nb && nb[x])
    {
      if (!isdigit(nb[x]) && nb[x] != '.')
	return (false);
      x++;
    }
  return (true);
}

int		send_message(int fd, char *message)
{
  if (!message)
    return (BAD_ARGUMENTS);
  if (send(fd, message, strlen(message), 0) == -1)
    return (FATAL_ERROR);
  if (send(fd, "\r\n", strlen("\r\n"), 0) == -1)
    return (FATAL_ERROR);
  return (SUCCESS);
}

bool  strcmp_contain_insensible(char *str, char *to_cmp)
{
  unsigned int   x;
  unsigned int   y;

  x = strlen(str);
  y = strlen(to_cmp);
  if (x < y)
    return (false);
  if (x >= y)
  {
    x = 0;
    y = 0;
    while (str[x] && to_cmp[y])
    {
      if (toupper(str[x]) != toupper(to_cmp[y]))
        break;
      y++;
      x++;
    }
    if (y == strlen(to_cmp))
      return (true);
  }
  return (false);
}
