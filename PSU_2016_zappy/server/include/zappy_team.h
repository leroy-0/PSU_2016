/*
** zappy_team.h for team in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 15:03:00 2017 yan
** Last update Fri Jun 23 12:53:04 2017 yan
*/

#ifndef			__ZAPPY_TEAM__
# define		__ZAPPY_TEAM__

#include		"zappy_list_player.h"

struct 			s_server;
struct 			s_player;

typedef struct		s_team
{
  char			name[256];
  t_list_player		*list;
  struct s_team		*next;
} t_team;

t_team			*create_team(char *name);
int			count_players(t_team *);
int			count_teams(struct s_server *server);
bool			send_teams(struct s_server *server, struct s_player *player);

#endif /* __ZAPPY_TEAM__ */
