/*
** opt_func.c for opt_func in /home/tekm/tek2/PSU_2016_zappy
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Jul  2 20:40:47 2017 leroy_0
** Last update Sun Jul  2 20:40:55 2017 leroy_0
*/

#include	<memory.h>
#include	"zappy_parsing.h"
#include	"zappy_args.h"

void		cpy_all_data(t_parse *parse, t_opt *opt)
{
  int		i;

  opt->port = parse->args.p_arg;
  opt->width = parse->args.x_arg;
  opt->height = parse->args.y_arg;
  opt->nb_client = parse->args.c_arg;
  opt->frequence = parse->args.f_arg;
  i = size_tab(parse->args.n_arg);
  opt->name_team = malloc(sizeof(char *) * (i + 1));
  i = 0;
  while (parse->args.n_arg[i] != NULL)
  {
    opt->name_team[i] = strdup(parse->args.n_arg[i]);
    i++;
  }
  opt->name_team[i] = NULL;
}
