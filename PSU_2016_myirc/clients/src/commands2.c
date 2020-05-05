/*
** commands2.c for commands in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:55:03 2017 leroy_0
** Last update Fri Jun  9 16:01:12 2017 yan
*/

#include 	"myirc.h"

int 		cmd_users(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_names(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_msg(char **cmd, t_connect **client)
{
  if (!*client)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_send_file(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_accept_file(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}
