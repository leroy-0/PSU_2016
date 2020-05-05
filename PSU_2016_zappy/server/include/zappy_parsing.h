/*
** zappy_server.h for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/include/zappy_server.h
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Jun 20 09:29:36 2017 Arthur Klein
** Last update Sun Jul  2 12:20:52 2017 yan
*/

#ifndef PROJECT_ZAPPY_SERVER_H
#define PROJECT_ZAPPY_SERVER_H

#include		<stdlib.h>
#include		<stdbool.h>

enum			INDEX
{
  CLIENT_INDEX = 0,
  FREQ_INDEX,
  HEIGHT_INDEX,
  HELP_INDEX,
  NAME_INDEX,
  PORT_INDEX,
  WIDTH_INDEX,
  NULL_INDEX
};

enum			ARGS
{
  PORT = 'p',
  WIDTH = 'x',
  HEIGHT = 'y',
  NAME = 'n',
  CLIENT = 'c',
  FREQ = 'f',
  HELP = 'h',
  ERROR = '?'
};

typedef struct		s_args
{
  int			p_arg;
  int			x_arg;
  int			y_arg;
  char			**n_arg;
  int			c_arg;
  int			f_arg;
}			t_args;

typedef struct		s_flags
{
  int			p_flag;
  int			x_flag;
  int			y_flag;
  int			n_flag;
  int			c_flag;
  int			f_flag;
  int			h_flag;
  int			error_flags;
}			t_flags;

typedef struct		s_parse
{
  struct s_flags	flags;
  struct s_args		args;
  struct s_ptrfunc	*ptr_func;
}			t_parse;

typedef struct		s_ptrfunc
{
  bool			(*ptr)(t_parse *, char **av, int ac);
  char			name;
  char			*str;
}			t_ptrfunc;

void			*x_malloc(size_t size);
t_parse			*init_parsing();
t_ptrfunc		*init_ptr_func();
bool			*parse_all_arg(t_parse *parse, int argc, char **argv);
bool			take_port(t_parse *parse, char **av, int ac);
bool			take_height(t_parse *parse, char **av, int ac);
bool			take_width(t_parse *parse, char **av, int ac);
bool			take_freq(t_parse *parse, char **av, int ac);
bool			take_client(t_parse *parse, char **av, int ac);
bool			take_name(t_parse *parse, char **av, int ac);
bool			take_help(t_parse *parse, char **av, int ac);
char			**recup_name_team(int argc, char **argv);
char			*recup_value(int argc, char **argv);
bool			is_a_number(char *str);
bool			check_all_error(t_parse *parse, bool *tab);
int			usage();
void			free_my_tab(char **tab);

#define			CHECK_FLAGS (parse->flags.f_flag != 1 \
|| parse->flags.c_flag != 1 \
|| parse->flags.n_flag != 1 || parse->flags.y_flag != 1 \
|| parse->flags.p_flag != 1 || parse->flags.x_flag != 1)
#define			CHECK_FLAGS_0 (parse->flags.f_flag < 1 \
|| parse->flags.c_flag < 1 || parse->flags.n_flag < 1 \
|| parse->flags.y_flag < 1 || parse->flags.p_flag < 1 \
|| parse->flags.x_flag < 1)
#endif //PROJECT_ZAPPY_SERVER_H
