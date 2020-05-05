/*
** tools_analyse.c for tools_analyse in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun May 21 21:37:48 2017 leroy_0
** Last update Sun May 21 21:37:49 2017 leroy_0
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myftp.h"

char        *epur_str(char *str)
{
  char      *tmp;
  int       i;
  int       k;

  i = 0;
  k = 0;
  if ((tmp = malloc(sizeof(*tmp) * (strlen(str) + 1))) == NULL)
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

int            count_words(char *str, char delim)
{
   int         x;
   int         y;

   x = 0;
   y = 0;
   while (str && str[x])
   {
      if (str[x] == delim)
         y++;
      x++;
   }
   y++;
   return (y);
}

char           **my_strtab(char *str, char *s)
{
   char        **tab;
   int         x;

   x = 1;
   if (!str)
      return (NULL);
   if ((tab = malloc(sizeof(char *) * (count_words(str, s[0]) + 1))) == NULL)
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

bool     strcmp_insensible(char *src, char *to_cmp)
{
  int   delim;
  int   x;

  x = 0;
  if (strlen(src) != strlen(to_cmp))
    return (false);
  if (strlen(src) > strlen(to_cmp))
    delim = strlen(src);
  else
    delim = strlen(to_cmp);
  while (x < delim)
  {
    if (toupper(src[x]) != toupper(to_cmp[x]))
      return (false);
    x++;
  }
  return (true);
}

char    *change_letters(char *str, char find, char replace)
{
  int   x;

  x = 0;
  while (str && str[x])
  {
    if (str[x] == find)
      str[x] = replace;
    x++;
  }
  return (str);
}
