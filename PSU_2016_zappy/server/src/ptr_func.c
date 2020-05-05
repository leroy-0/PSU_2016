/*
** ptr_func.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/ptr_func.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Wed Jun 21 09:33:03 2017 Arthur Klein
** Last update Sat Jul  1 14:18:02 2017 Bachelet
*/

#include	<memory.h>
#include	<stdio.h>
#include	"zappy_parsing.h"

bool		take_port(t_parse *parse, char **av, int ac)
{
  char		*str;

  str = recup_value(ac, av);
  parse->flags.p_flag++;
  if (!is_a_number(str))
    return (false);
  parse->args.p_arg = atoi(str);
  free(str);
  return (true);
}

bool		take_height(t_parse *parse, char **av, int ac)
{
  char		*str;

  str = recup_value(ac, av);
  parse->flags.y_flag++;
  if (!is_a_number(str))
    return (false);
  if ((parse->args.y_arg = atoi(str)) < 13)
    {
      fprintf(stderr, "Minimun Height should be 13\n");
      return (false);
    }
  free(str);
  return (true);
}

bool		take_width(t_parse *parse, char **av, int ac)
{
  char		*str;

  str = recup_value(ac, av);
  if (!is_a_number(str))
    return (false);
  if ((parse->args.x_arg = atoi(str)) < 13)
    {
      fprintf(stderr, "Minimun Width should be 13\n");
      return (false);
    }
  parse->flags.x_flag++;
  free(str);
  return (true);
}

bool		take_freq(t_parse *parse, char **av, int ac)
{
  char		*str;

  str = recup_value(ac, av);
  if (!is_a_number(str))
    return (false);
  parse->args.f_arg = atoi(str);
  if ((parse->args.f_arg = atoi(str)) < 2)
    {
      fprintf(stderr, "Minimun frequence should be 2\n");
      return (false);
    }
  parse->flags.f_flag++;
  return (true);
}
