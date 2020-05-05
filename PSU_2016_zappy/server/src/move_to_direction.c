/*
** move_to_direction.c for move_to_direction in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Fri Jun 23 12:27:07 2017 Adrien Bachelet
** Last update Fri Jun 30 13:10:45 2017 Bachelet
*/

#include	"zappy_server.h"
#include	"zappy_player.h"

void		update_new_pos(t_dir direction, t_pos *new_pos, t_info info)
{
  if (direction == UP && new_pos->y > 0)
    new_pos->y--;
  else if (direction == UP)
    new_pos->y = info.height - 1;
  else if (direction == RIGHT && new_pos->x < info.width - 1)
    new_pos->x++;
  else if (direction == RIGHT)
    new_pos->x = 0;
  else if (direction == LEFT && new_pos->x > 0)
    new_pos->x--;
  else if (direction == LEFT)
    new_pos->x = info.width - 1;
  else if (direction == DOWN && new_pos->y < info.height - 1)
    new_pos->y++;
  else
    new_pos->y = 0;
  return ;
}
