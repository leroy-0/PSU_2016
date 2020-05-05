/*
** look.h for look in /home/adrien/rendu/PSU_2016_zappy/server/include
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Wed Jun 21 16:29:43 2017 Adrien Bachelet
** Last update Wed Jun 21 16:30:04 2017 Adrien Bachelet
*/

#ifndef		LOOK_H_
# define	LOOK_H_

#include "zappy_player.h"
#include "zappy_tile.h"

char		*look(t_pos *, t_tile **, t_dir);
char		*look_top(t_pos *, t_tile **);
char		*look_right(t_pos *, t_tile **);
char		*look_left(t_pos *, t_tile **);
char		*look_bottom(t_pos *, t_tile **);

#endif		/* !LOOK_H_ */
