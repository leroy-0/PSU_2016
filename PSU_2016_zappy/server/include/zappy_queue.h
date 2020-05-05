/*
** zappy_queue.h for zappy queue in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 28 18:21:09 2017 yan
** Last update Sun Jul  2 20:44:44 2017 leroy_0
*/

#ifndef			__ZAPPY_QUEUE__
# define		__ZAPPY_QUEUE__

#include		<bits/types.h>

#include		"zappy_ptr.h"

typedef struct		s_queue
{
  double	start;
  t_ptr_cmd		func;
  char			*line;
  struct s_queue	*next;
} t_queue;

int		add_queue(struct s_player *player, char *line, t_ptr_cmd func);
int		remove_queue(struct s_player *player, t_queue *message);

#endif /* __ZAPPY_QUEUE__ */
