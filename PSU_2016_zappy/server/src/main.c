/*
** main.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/main.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Jun 20 09:28:59 2017 Arthur Klein
** Last update Sun Jul  2 12:22:19 2017 yan
*/
#include	<ctype.h>
#include	<stdio.h>
#include	<stdlib.h>
#include 	<time.h>
#include	"zappy_map.h"
#include	"zappy_parsing.h"
#include	"zappy_args.h"
#include	"zappy_server.h"

static t_team		*find_winner(t_server *server)
{
  t_team		*team;
  t_list_player		*player;
  int			count;

  team = server->team;
  count = 0;
  while (team && count < 6)
  {
    count = 0;
    player = team->list;
    while (player)
    {
      if (player->player->elevation == 6)
	count++;
      player = player->next;
    }
    if (count < 6)
      team = team->next;
  }
  return (team);
}

static int		check_end(t_server *server)
{
  t_team		*team;
  char			msg[MSG_LENGTH];

  team = find_winner(server);
  if (team != NULL)
  {
    sprintf(msg, "seg %s", team->name);
    send_graphical(server, msg);
    return (true);
  }
  return (false);
}

static int		run_server(t_server *server)
{
  int			status;
  struct timeval	time;

  time.tv_sec = 1;
  time.tv_usec = 0;
  status = 0;
  while (status == 0 && check_end(server) == false)
  {
    reset_select(server);
    if ((select(server->connect->max_fd + 1, &(server->connect->fdset),
		NULL, NULL, &time)) == -1)
      return (-1);
    update_queues(server);
    getrusage(RUSAGE_SELF, &server->time);
    status = analyse_select(server);
  }
  free_server(server);

  return (0);
}

int		main(int argc, char **argv)
{
  t_parse	*parse;
  t_opt		opt;
  t_server	*server;
  bool		*tab;

  parse = init_parsing();
  srand(time(NULL));
  parse->ptr_func = init_ptr_func();
  tab = parse_all_arg(parse, argc, argv);
  if (!check_all_error(parse, tab))
    return (84);
  free(tab);
  cpy_all_data(parse, &opt);
  if ((server = create_server(&opt)) == NULL)
    return (-1);
  server->map = create_map(opt.width, opt.height);
  free_my_tab(parse->args.n_arg);
  free(parse->ptr_func);
  free(parse);
  return (run_server(server));
}
