/*
** utils.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/utils.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Jun 20 10:58:08 2017 Arthur Klein
** Last update Fri Jun 30 17:45:17 2017 Bachelet
*/

#include	<stdlib.h>
#include	<stdbool.h>
#include	<ctype.h>
#include	<stdio.h>
#include	"zappy_parsing.h"

t_parse		*init_parsing()
{
  t_parse	*parse;

  parse = x_malloc(sizeof(t_parse));
  parse->args.c_arg = 0;
  parse->args.f_arg = -1;
  parse->args.n_arg = NULL;
  parse->args.p_arg = 0;
  parse->args.x_arg = 0;
  parse->args.y_arg = 0;
  parse->flags.c_flag = 0;
  parse->flags.f_flag = 0;
  parse->flags.n_flag = 0;
  parse->flags.p_flag = 0;
  parse->flags.x_flag = 0;
  parse->flags.y_flag = 0;
  parse->flags.h_flag = 0;
  parse->flags.error_flags = 0;
  return (parse);
}

bool		is_a_number(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
  {
    if (!isdigit(str[i]))
      return (false);
    i++;
  }
  return (true);
}

void		*x_malloc(size_t size)
{
  void		*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    exit(84);
  return (ptr);
}

int		size_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i] != NULL)
    i++;
  return (i);
}

void		free_my_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}
