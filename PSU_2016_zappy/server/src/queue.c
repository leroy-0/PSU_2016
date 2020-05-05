/*
** queue.c for queue in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 28 18:17:51 2017 yan
** Last update Sun Jul  2 12:27:19 2017 yan
*/

#include	<string.h>
#include	<stdlib.h>
#include 	<time.h>
#include	"zappy_server.h"
#include	"zappy_queue.h"

static int	count_queue(t_player *player)
{
  int		back;
  t_queue	*tmp;

  back = 0;
  tmp = player->queue;
  while (tmp)
  {
    back++;
    tmp = tmp->next;
  }
  if (back >= 10)
    send_message(player->fd, "ko");
  return (back);
}

int		add_queue(t_player *player, char *line, t_ptr_cmd func)
{
  t_queue	*tmp;
  t_queue 	*create;

  if (count_queue(player) >= 10)
    return (1);
  tmp = player->queue;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if ((create = malloc(sizeof(t_player))) == NULL)
    return (-1);
  create->next = NULL;
  create->func = func;
  create->start = -1;
  create->line = strdup(line);
  if (tmp == NULL)
    player->queue = create;
  else
    tmp->next = create;
  return (0);
}

int		remove_queue(t_player *player, t_queue *message)
{
  t_queue	*tmp;
  t_queue	*before;

  tmp = player->queue;
  before = NULL;
  while (tmp && tmp != message)
  {
    before = tmp;
    tmp = tmp->next;
  }
  if (tmp != NULL)
  {
    if (before == NULL)
      player->queue = tmp->next;
    else
      before->next = tmp->next;
    free(tmp->line);
    free(tmp);
  }
  return (0);
}

static int	update_queue(t_server *server, t_player *player)
{
  t_queue	*tmp;
  double	time_now;

  tmp = player->queue;
  time_now = (double)clock() / (double)CLOCKS_PER_SEC;
  if (player->team == true && strcmp(player->name_team, GRAPHICAL_NAME) != 0
    && update_life(server, player, time_now) == 1)
    return (1);
  if (tmp != NULL)
  {
    if (tmp->start == -1)
    {
      send_info(server, tmp, player);
      tmp->start = time_now;
    }
    if (tmp->func.time == 0 ||
	time_now - tmp->start >= ((double)tmp->func.time /
				  (double)server->info.freq))
    {
      tmp->func.ptr(server, tmp->line, player);
      remove_queue(player, tmp);
    }
  }
  return (0);
}

void		update_queues(t_server *server)
{
  t_player 	*tmp;
  int 		status;

  tmp = server->player;
  status = 0;
  while (tmp != NULL && status == 0) {
    status = update_queue(server, tmp);
    if (status == 0)
      tmp = tmp->next;
  }
}
