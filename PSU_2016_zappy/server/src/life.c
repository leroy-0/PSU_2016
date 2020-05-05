/*
** life.c for life in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Sun Jul  2 12:39:49 2017 yan
** Last update Sun Jul  2 19:28:56 2017 Bachelet
*/

#include	<string.h>
#include	<stdlib.h>
#include 	<time.h>
#include	"zappy_server.h"
#include	"zappy_queue.h"

int		update_life(t_server *server, t_player *player, double time_now)
{
  double	diff;

  diff = (player->health.last == -1) ? -1 : (time_now - player->health.last);
  player->health.last = time_now;
  if (diff > 0)
    {
      player->health.life -= diff;
      if (player->health.life <= 0 && player->inventory[FOOD] != 0) {
	player->inventory[FOOD]--;
	player->health.life = 126 / server->info.freq;
      } else if (player->inventory[FOOD] == 0)
	{
	  death(server, player);
	  return (1);
	}
    }
  return (0);
}
