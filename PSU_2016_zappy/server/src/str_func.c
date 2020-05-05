/*
** str_func.c for str_func in /home/yan/Documents/psu/PSU_2016_zappy/server
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Tue Jun 27 13:44:23 2017 yan
** Last update Tue Jun 27 13:47:28 2017 yan
*/

#include	<string.h>
#include	<stdlib.h>

char		*epur_str(char *str)
{
  char		*tmp;
  int		i;
  int		k;

  i = 0;
  k = 0;
  if ((tmp = malloc(sizeof(char) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while ((str[i] == ' ') || (str[i] == '\t'))
    i++;
  while (str[i] != '\0')
    {
      tmp[k++] = str[i++];
      while ((str[i] == ' ') || (str[i] == '\t'))
	i++;
      if (((str[i - 1] == ' ') || (str[i - 1] == '\t')) && (str[i] != '\0'))
	{
	  tmp[k] = ' ';
	  k++;
	}
    }
  tmp[k] = '\0';
  free(str);
  return (tmp);
}
