/*
** zappy_list_player.h for list_player in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Thu Jun 29 15:40:19 2017 yan
** Last update Thu Jun 29 15:40:22 2017 yan
*/

#ifndef			__ZAPPY_LIST_PLAYER__
# define		__ZAPPY_LIST_PLAYER__

#include		"zappy_player.h"

typedef struct		s_list_player
{
  t_player		*player;
  struct s_list_player	*next;
} t_list_player;

t_list_player		*create_list_player(t_player *);
void			add_list_player(t_list_player **, t_list_player *);

#endif /* __ZAPPY_LIST__ */
