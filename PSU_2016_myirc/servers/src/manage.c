/*
** manage.c for manage in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 24 17:02:59 2017 leroy_0
** Last update Thu Jun  8 11:51:01 2017 yan
*/

#include "myirc.h"
#include "fnc_ptrs.h"

t_client    *find_client_in_channel(t_channel *channel, char *nickname)
{
  t_name   *tmp;

  tmp = channel->connected;
  while (tmp)
  {
    if (strcmp_insensible(tmp->user->nickname, nickname))
      return (tmp->user);
    tmp = tmp->next;
  }
  return (NULL);
}

int     manage_commands(char *buffer, t_client *client, t_connect *server)
{
  t_cmd   *ptrs;
  char  **cmds;
  int   x;

  x = 0;
  if ((ptrs = init_ptrs()) == NULL
    || (cmds = my_strtab(buffer, " ")) == NULL)
    return (FATAL_ERROR);
  if (!cmds[0])
    return (SUCCESS);
  while (ptrs[x].cmd)
  {
    if (strcmp_insensible(ptrs[x].cmd, cmds[0]))
      return ((ptrs[x].func)(cmds, client, server));
    x++;
  }
  x--;
  return ((ptrs[x].func)(cmds, client, server));
}
