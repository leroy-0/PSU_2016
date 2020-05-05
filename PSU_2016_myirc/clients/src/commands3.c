/*
** commands3.c for commands3 in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 18:07:02 2017 leroy_0
** Last update Fri Jun  9 16:01:43 2017 yan
*/

#include <fcntl.h>
#include "myirc.h"

int 		cmd_quit(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (SUCCESS);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  free(*client);
  *client = NULL;
  return (SUCCESS);
}

int 		cmd_help(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (SUCCESS);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int     cmd_active(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (SUCCESS);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_other(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (SUCCESS);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_user(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (SUCCESS);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}
