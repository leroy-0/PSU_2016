/*
** zappy_ptr.h for ptr in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Thu Jun 29 14:31:30 2017 yan
** Last update Thu Jun 29 14:31:47 2017 yan
*/

#ifndef			__ZAPPY_PTR__
# define		__ZAPPY_PTR__

struct			s_server;
struct			s_player;

typedef struct		s_ptr_cmd
{
  bool			(*ptr)(struct s_server *, char *, struct s_player *);
  char			*cmd;
  int			time;
}			t_ptr_cmd;

#define 		PTR_ERROR (12)

#endif /* __ZAPPY_PTR__ */
