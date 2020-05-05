/*
** zappy_args.h for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/include/zappy_args.h
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Wed Jun 21 13:21:29 2017 Arthur Klein
** Last update Sun Jul  2 12:18:20 2017 yan
*/

#ifndef			__PROJECT_ZAPPY_ARGS_H__
# define		__PROJECT_ZAPPY_ARGS_H__

typedef struct		s_opt
{
  int			port;
  int			width;
  int			height;
  char			**name_team;
  int			nb_client;
  int			frequence;
}			t_opt;

int			size_tab(char **tab);
void			cpy_all_data(t_parse *parse, t_opt *opt);

#endif			/* __PROJECT_ZAPPY_ARGS_H__ */
