/*
** eject.c for eject in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Sun Jul  2 13:39:38 2017 Bachelet
** Last update Sun Jul  2 20:43:19 2017 leroy_0
*/

#include	"zappy_server.h"

void            set_pos(t_server *server, t_player *player, t_pos *pos,
			t_dir dir)
{
  pos->x = player->pos.x;
  pos->y = player->pos.y;
  if (dir == UP || dir == DOWN)
    {
      pos->y = (dir == DOWN) ? pos->y + 1 : pos->y - 1;
      if (pos->y < 0)
        pos->y = server->info.height - 1;
      else if (pos->y >= server->info.height)
        pos->y = 0;
    }
  else if (dir == RIGHT || player->dir == LEFT)
    {
      pos->x = (dir == RIGHT) ? pos->x + 1 : pos->x - 1;
      if (pos->x < 0)
        pos->x = server->info.width - 1;
      else if (pos->x >= server->info.width)
        pos->x = 0;
    }
}

void            eject_player(t_server *server, t_player *player, t_dir dir)
{
  t_dir		tmp;

  tmp = player->dir;
  player->dir = dir;
  forward(server, "", player);
  player->dir = tmp;
}

bool            eject(t_server *server, char *line, t_player *player)
{
  t_pos         pos;
  t_player      *tmp;

  (void)line;
  set_pos(server, player, &pos, player->dir);
  tmp = server->player;
  while (tmp)
    {
      if (tmp->pos.x == pos.x && tmp->pos.y == pos.y)
	eject_player(server, tmp, player->dir);
      tmp = tmp->next;
    }
  send_message(player->fd, "ok");
  return (true);
}
