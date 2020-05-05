/*
** commands.c for commands in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:54:57 2017 leroy_0
** Last update Fri Jun  9 16:32:01 2017 yan
*/

#include	"fnc_ptrs.h"
#include 	"myirc.h"

int		manage_commands(char *buffer, t_connect **client)
{
  t_cmd		*ptrs;
  char		**cmds;
  int		x;
  int		back;

  x = 0;
  if ((ptrs = init_ptrs()) == NULL
      || (cmds = my_strtab(buffer, " ")) == NULL
      || !cmds[0])
    return (-1);
  while (ptrs[x].cmd)
    {
      if (strcmp_insensible(ptrs[x].cmd, cmds[0]))
        {
	  back = (ptrs[x].func)(cmds, client);
	  free_tab(&cmds);
	  return (back);
	}
      x++;
    }
  x--;
  back = (ptrs[x].func)(cmds, client);
  free_tab(&cmds);
  return (back);
}

int 		cmd_server(char **cmd, t_connect **client)
{
  char		*ip;
  char		*port;

  if (!cmd[1] || check_connection(cmd[1], &ip, &port) == false)
    return (BAD_ARGUMENTS);
  if (*client != NULL)
    close_client(client);
  if ((*client = create_client(inet_addr(ip), ntohs(atoi(port)))) == NULL)
    return (BAD_CONNECTION);
  free(ip);
  free(port);
  return (SUCCESS);
}

int 		cmd_nick(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_list(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}

int 		cmd_join(char **cmd, t_connect **client)
{
  if (*client == NULL)
    return (NOT_CONNECTED);
  remove_slash(cmd);
  send_cmd(cmd, *client);
  return (SUCCESS);
}
