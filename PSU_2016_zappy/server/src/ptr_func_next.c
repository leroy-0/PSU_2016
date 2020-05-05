/*
** ptr_func_next.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/ptr_func_next.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Wed Jun 21 12:58:08 2017 Arthur Klein
** Last update Sat Jul  1 14:18:51 2017 Bachelet
*/

#include	<stdbool.h>
#include	<stdio.h>
#include	"zappy_parsing.h"

void		init_ptr_func_next(t_ptrfunc *ptr)
{
  ptr[NAME_INDEX].ptr = &take_name;
  ptr[NAME_INDEX].name = NAME;
  ptr[NAME_INDEX].str = "The argument of -n must be a string\n";
  ptr[PORT_INDEX].ptr = &take_port;
  ptr[PORT_INDEX].name = PORT;
  ptr[PORT_INDEX].str = "The argument of -p must be a integer\n";
  ptr[WIDTH_INDEX].ptr = &take_width;
  ptr[WIDTH_INDEX].name = WIDTH;
  ptr[WIDTH_INDEX].str = "The argument of -x must be a integer\n";
  ptr[NULL_INDEX].ptr = NULL;
  ptr[NULL_INDEX].name = '\0';
}

t_ptrfunc	*init_ptr_func()
{
  t_ptrfunc	*ptr;

  ptr = malloc(sizeof(t_ptrfunc) * 8);
  ptr[CLIENT_INDEX].ptr = &take_client;
  ptr[CLIENT_INDEX].name = CLIENT;
  ptr[CLIENT_INDEX].str = "The argument of -c must be a integer\n";
  ptr[FREQ_INDEX].ptr = &take_freq;
  ptr[FREQ_INDEX].name = FREQ;
  ptr[FREQ_INDEX].str = "The argument of -f must be a integer\n";
  ptr[HEIGHT_INDEX].ptr = &take_height;
  ptr[HEIGHT_INDEX].name = HEIGHT;
  ptr[HEIGHT_INDEX].str = "The argument of -y must be a integer\n";
  ptr[HELP_INDEX].ptr = &take_help;
  ptr[HELP_INDEX].name = HELP;
  ptr[HELP_INDEX].str = "";
  init_ptr_func_next(ptr);
  return (ptr);
}

bool		take_client(t_parse *parse, char **av, int ac)
{
  char		*str;

  str = recup_value(ac, av);
  if (!is_a_number(str))
    return (false);
  if ((parse->args.c_arg = atoi(str)) <= 0)
    {
      fprintf(stderr, "Number of client should be greater than 0\n");
      return (false);
    }
  free(str);
  parse->flags.c_flag++;
  return (true);
}

bool		take_name(t_parse *parse, char **av, int ac)
{
  if ((parse->args.n_arg = recup_name_team(ac, av)) == NULL)
    {
      fprintf(stderr, "You Should specify one name of team\n");
      return (false);
    }
  parse->flags.n_flag++;
  return (true);
}

bool		take_help(t_parse *parse, char **av, int ac)
{
  (void)av;
  (void)ac;
  parse->flags.h_flag++;
  return (true);
}
