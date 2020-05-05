/*
** check_error_parsing.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/check_error_parsing.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Wed Jun 21 13:11:41 2017 Arthur Klein
** Last update Sun Jul  2 12:24:02 2017 yan
*/
#include	<stdbool.h>
#include	<stdio.h>
#include	"zappy_parsing.h"

bool		check_error_arg(t_parse *parse, bool *tab)
{
  bool		state;
  int		i;

  i = 0;
  state = true;
  while (i < 9)
  {
    if (!tab[i])
    {
      state = false;
      fprintf(stderr, parse->ptr_func[i].str);
    }
    i++;
  }
  return (state);
}
bool		check_all_error(t_parse *parse, bool *tab)
{
  if (parse->flags.f_flag == 0)
  {
    parse->args.f_arg = 100;
    parse->flags.f_flag++;
  }
  if (parse->flags.h_flag > 0)
    return ((bool)(usage()));
  if (!check_error_arg(parse, tab))
    return (false);
  if (parse->flags.error_flags != 0)
  {
    fprintf(stderr, "Error option\n");
    return (false);
  }
  if (CHECK_FLAGS)
  {
    if (CHECK_FLAGS_0)
      return ((bool)usage());
    fprintf(stderr, "Error Option use more one time\n");
    return (false);
  }
  return (true);
}
