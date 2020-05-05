/*
** create_map.h for create_map in /home/adrien/rendu/PSU_2016_zappy/server/include
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Wed Jun 21 11:41:32 2017 Adrien Bachelet
** Last update Wed Jun 28 17:04:14 2017 Bachelet
*/

#ifndef		CREATE_MAP_H_
# define	CREATE_MAP_H_

#include	"zappy_tile.h"

t_tile		**create_map(int, int);
char		*get_info_tile(t_tile);

#endif		/* !CREATE_MAP_H_ */
