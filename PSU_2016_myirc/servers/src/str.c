/*
** str.c for str in /home/yan/Documents/psu/PSU_2016_myftp
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Thu May 11 15:45:42 2017 yan
** Last update Sun May 21 17:08:18 2017 yan
*/

#include	<stdlib.h>

static int	get_pos(int start, char *word, int *len)
{
  int           c;

  c = start;
  while (word[c] != ' ' && word[c] != '\0' && word[c] != '\t')
    c++;
  (*len) = c - start + 1;
  return (c);
}

static int	get_start(int start, char *word)
{
  while ((word[start] == ' ' || word[start] == '\t') &&
	 word[start] != '\0')
    start++;
  return (start);
}

int		word_count(char *word)
{
  int		c;
  int		len;

  len = 0;
  c = 1;
  while (word[c] != '\0')
    {
      if ((word[c] != ' ' && word[c - 1] == ' ') ||
          (word[c] != '\t' && word[c - 1] == '\t'))
        len++;
      c++;
    }
  return (len + 1);
}

void            free_tab(char **array, int opt)
{
  int           a;

  a = 0;
  while (array[a])
    {
      free(array[a]);
      a++;
    }
  if (opt == 0)
    free(array);
}

char		**line_to_tab(char *word, int start, int num)
{
  char		**back;
  int		a[3];
  int		len;

  a[0] = 0;
  if ((back = malloc(sizeof(char *) * (num + 1))) == NULL)
    return (NULL);
  while (a[0] < num)
    {
      a[2] = 0;
      a[1] = get_pos(start, word, &len);
      if ((back[a[0]] = malloc(sizeof(char) * len)) == NULL)
	return (NULL);
      while (start < a[1])
        {
          back[a[0]][a[2]] = word[start];
          a[2]++;
          start++;
        }
      back[a[0]][a[2]] = '\0';
      start = get_start(start, word);
      a[0]++;
    }
  back[a[0]] = NULL;
  return (back);
}
