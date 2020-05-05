/*
** msg.c for msg in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon Jun  5 14:43:05 2017 leroy_0
** Last update Fri Jun  9 19:41:39 2017 yan
*/

#include 		"myirc.h"

char 			*get_formated_time()
{
  time_t 		rawtime;
  struct tm		*timeinfo;
  char			*msg;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  msg = asctime(timeinfo);
  msg[strlen(msg) - 1] = ' ';
  return (msg);
}

void 			send_msg(char *nickname, int fd, char **cmd, int start)
{
  char			*msg;
  char			send[4096];

  msg = get_formated_time();
  sprintf(send, "%s%s : ", msg, nickname);
  while (cmd[start])
    {
      strcat(send, cmd[start]);
      strcat(send, " ");
      start++;
    }
  send_message(fd, send);
}

void 			send_to_all(t_channel *channel, char **cmd, char *nickname)
{
  t_name	 	*tmp;

  if (!channel)
    return ;
  tmp = channel->connected;
  while (tmp)
    {
      if (!strcmp_insensible(tmp->user->nickname, nickname))
	send_msg(nickname, tmp->user->fd, cmd, 0);
      tmp = tmp->next;
    }
}
