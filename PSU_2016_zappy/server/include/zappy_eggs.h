/*
** zappy_eggs.h for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/include/zappy_eggs.h
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jul 01 07:23:42 2017 Arthur Klein
** Last update Sun Jul  2 12:20:00 2017 yan
*/

#ifndef			__PROJECT_ZAPPY_EGGS_H__
# define		__PROJECT_ZAPPY_EGGS_H__

typedef struct		s_eggs
{
  int			id;
  bool			activate;
  struct s_eggs		*next;
}			t_eggs;

t_eggs			*init_eggs_node(t_eggs *list);
t_eggs			*init_eggs_list(t_eggs *list);

#endif			/* __PROJECT_ZAPPY_EGGS_H__ */
