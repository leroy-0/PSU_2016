/*
** tools.c for tools in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:35:15 2017 leroy_0
** Last update Wed Jun  7 19:58:35 2017 yan
*/

#include <ctype.h>
#include "common.h"

char        *epur_str(char *str)
{
  char      *tmp;
  int       i;
  int       k;

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

int       count_words(char *str, char *delim)
{
  unsigned int    x;
  unsigned int    y;
  unsigned int    z;
  unsigned int    total;

  x = 0;
  total = 0;
  if (!delim || !str)
    return (0);
  while (x <= strlen(str))
  {
    z = 0;
    y = 0;
    while (delim[z])
    {
      if (x + z <= strlen(str) && str[x + z] == delim[z])
        y++;
      z++;
    }
    x++;
    if (y == strlen(delim))
      total++;
  }
  total++;
  return (total);
}

char           **my_strtab(char *str, char *s)
{
   char        **tab;
   int         x;

   x = 1;
   if (!str)
      return (NULL);
   if ((tab = malloc(sizeof(char *) * (count_words(str, s) + 1))) == NULL)
      return (NULL);
   tab[0] = strtok(str, s);
   if (tab[0])
      tab[0] = strdup(tab[0]);
   while (tab && tab[x - 1])
   {
      tab[x] = strtok(NULL, s);
      if (tab[x])
         tab[x] = strdup(tab[x]);
      x++;
   }
   free(str);
   return (tab);
}

bool            check_validity(char **buff)
{
  unsigned int  x;

  x = 0;
  if (strcmp(*buff, "") == 0
    || (*buff)[0] == '\n' || (*buff)[0] == '\r')
    return (false);
  if ((*buff)[strlen(*buff) - 1] == '\n')
    (*buff)[strlen(*buff) - 1] = '\0';
  while (*buff && (*buff)[x])
  {
    if ((*buff)[x] == ' ')
      x++;
    else
      break;
  }
  if (!(strlen(*buff) == x))
    *buff = epur_str(*buff);
  return (true);
}

bool     strcmp_insensible(char *src, char *to_cmp)
{
  int   delim;
  int   x;

  x = 0;
  if (src == NULL || to_cmp == NULL || strlen(src) != strlen(to_cmp))
    return (false);
  delim = strlen(to_cmp);
  while (x < delim)
  {
    if (toupper(src[x]) != toupper(to_cmp[x]))
      return (false);
    x++;
  }
  return (true);
}
