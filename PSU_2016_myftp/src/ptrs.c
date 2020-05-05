/*
** ptrs.c for ptrs in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 10 15:16:33 2017 leroy_0
** Last update Wed May 10 15:16:42 2017 leroy_0
*/

#include "myftp.h"

struct s_cmd 		*init_ptrs2(struct s_cmd *tab)
{
	tab[8].cmd = "PORT";
	tab[8].func = &cmd_port;
	tab[9].cmd = "HELP";
	tab[9].func = &cmd_help;
	tab[10].cmd = "NOOP";
	tab[10].func = &cmd_noop;
	tab[11].cmd = "RETR";
	tab[11].func = &cmd_download;
	tab[12].cmd = "STOR";
	tab[12].func = &cmd_upload;
	tab[13].cmd = "LIST";
	tab[13].func = &cmd_list;
	tab[14].cmd = NULL;
	tab[14].func = NULL;
	return (tab);
}

struct s_cmd		*init_ptrs()
{
  struct s_cmd		*tab;

  if ((tab = malloc(sizeof(struct s_cmd) * 15)) == NULL)
  	return (NULL);
  tab[0].cmd = "USER";
  tab[0].func = &cmd_user;
  tab[1].cmd = "PASS";
  tab[1].func = &cmd_pass;
  tab[2].cmd = "CWD";
  tab[2].func = &cmd_cwd;
  tab[3].cmd = "CDUP";
  tab[3].func = &cmd_cdup;
  tab[4].cmd = "QUIT";
  tab[4].func = &cmd_disconnect;
  tab[5].cmd = "DELE";
  tab[5].func = &cmd_delete;
  tab[6].cmd = "PWD";
  tab[6].func = &cmd_pwd;
  tab[7].cmd = "PASV";
  tab[7].func = &cmd_passive;
  return (init_ptrs2(tab));
}
