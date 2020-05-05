/*
** send_func.c for send_func in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Sat Jul  1 14:21:02 2017 Bachelet
** Last update Sat Jul  1 14:23:04 2017 Bachelet
*/

#include	<string.h>
#include	<ctype.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"zappy_server.h"

bool		send_message(int fd, char *message)
{
  char		*sent;

  if (!message ||
      (sent = malloc(sizeof(message) + strlen(message) + 1)) == NULL)
    return (false);
  strcpy(sent, message);
  sent[strlen(message)] = '\n';
  sent[strlen(message) + 1] = '\0';
  if (send(fd, sent, strlen(sent), 0) == -1)
    return (false);
  free(sent);
  return (true);
}

bool		send_info(t_server *server, t_queue *tmp, t_player *player)
{
  char		msg[MSG_LENGTH];

  if (strcasecmp("Fork", tmp->line) == 0)
  {
    if (!player->eggs->activate)
      player->eggs->activate = true;
    else
    {
      player->eggs = init_eggs_node(player->eggs);
      player->eggs->activate = true;
    }
    sprintf(msg, "pfk %d", player->id);
    if (send_graphical(server, msg) == false)
      return (false);
  }
  else if (strcasecmp("Incantation", tmp->line) == 0)
  {
    send_message(player->fd, "Elevation underway");
    sprintf(msg, "pic %d\n", player->id);
    if (send_graphical(server, msg) == false)
      return (false);
  }
  return (true);
}

