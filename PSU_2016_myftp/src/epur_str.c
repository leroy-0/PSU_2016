/*
** epur_str.c for epur_str in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 18:16:15 2017 leroy_0
** Last update Thu May 18 18:16:16 2017 leroy_0
*/

#include <stdio.h>
#include <stdlib.h>

char		*epur_str(char *str)
{
  char		*tmp;
  int		i;
  int		k;

  i = 0;
  k = 0;
  if ((tmp = malloc(sizeof(*tmp) * (my_strlen(str) + 1))) == NULL)
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
