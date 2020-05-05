/*
** gest_command.c for PSU_2016_zappy in /home/kleinh/Documents/PSU_2016_zappy/server/src/gest_command.c
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Jun 27 09:31:28 2017 Arthur Klein
** Last update Wed Jun 28 16:48:41 2017 Bachelet
*/
#include		<memory.h>
#include		"zappy_server.h"

int			do_loop_command(t_ptr_cmd *ptr, char *str, t_player *player)
{
  int			i;

  i = 0;
  while (str != NULL)
  {
    while (ptr[i].ptr != NULL)
    {
      if (strncmp(ptr[i].cmd, str, strlen(ptr[i].cmd)) == 0)
      {
	add_queue(player, str, ptr[i]);
	return (0);
      }
      i++;
    }
    add_queue(player, str, ptr[PTR_ERROR]);
    str = strtok(NULL, "\n");
    i = 0;
  }
  return (0);
}

int			gest_command(t_player *player, t_server *server, char *line)
{
  static  t_ptr_cmd	*ptr = NULL;
  char			*str;

  if (ptr == NULL)
    ptr = init_my_ptr_func_cmd();
  str = strtok(line, "\n");
  if (!player->team)
    {
      add_player_to_team(server, line, player);
      return (0);
    }
  return (do_loop_command(ptr, str, player));
}
