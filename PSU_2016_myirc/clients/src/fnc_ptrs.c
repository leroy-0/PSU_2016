/*
** fnc_ptrs.c for fnc_ptrs in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:42:45 2017 leroy_0
** Last update Fri Jun  9 16:25:27 2017 yan
*/

#include	"fnc_ptrs.h"

struct s_cmd 	*init_ptrs2(struct s_cmd *tab)
{
  tab[8].cmd = "/send_file";
  tab[8].func = &cmd_send_file;
  tab[9].cmd = "/accept_file";
  tab[9].func = &cmd_accept_file;
  tab[10].cmd = "/quit";
  tab[10].func = &cmd_quit;
  tab[11].cmd = "/help";
  tab[11].func = &cmd_help;
  tab[12].cmd = "/active";
  tab[12].func = &cmd_active;
  tab[13].cmd = "/user";
  tab[13].func = &cmd_user;
  tab[14].cmd = "";
  tab[14].func = &cmd_other;
  tab[15].cmd = NULL;
  tab[15].func = NULL;
  return (tab);
}

struct s_cmd	*init_ptrs()
{
  struct s_cmd	*tab;

  if ((tab = malloc(sizeof(struct s_cmd) * 16)) == NULL)
  	return (NULL);
  tab[0].cmd = "/server";
  tab[0].func = &cmd_server;
  tab[1].cmd = "/nick";
  tab[1].func = &cmd_nick;
  tab[2].cmd = "/list";
  tab[2].func = &cmd_list;
  tab[3].cmd = "/join";
  tab[3].func = &cmd_join;
  tab[4].cmd = "/part";
  tab[4].func = &cmd_part;
  tab[5].cmd = "/users";
  tab[5].func = &cmd_users;
  tab[6].cmd = "/names";
  tab[6].func = &cmd_names;
  tab[7].cmd = "/msg";
  tab[7].func = &cmd_msg;
  return (init_ptrs2(tab));
}
