/*
** fnc_ptrs.h for fnc_ptrs in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 15:43:37 2017 leroy_0
** Last update Wed Jun  7 19:20:56 2017 yan
*/

#ifndef 	__FNC_PTRS__
# define 	__FNC_PTRS__

# include 	"myirc.h"

typedef struct	s_cmd
{
  int          	(*func)(char **cmd, t_client *client, t_connect *server);
  char			*cmd;
}				t_cmd;

//INIT
struct s_cmd		*init_ptrs();

//FONCTION POINTERS
int 		cmd_user(char **cmd, t_client *client, t_connect *server);
int 		cmd_server(char **cmd, t_client *client, t_connect *server);
int 		cmd_nick(char **cmd, t_client *client, t_connect *server);
int 		cmd_list(char **cmd, t_client *client, t_connect *server);
int 		cmd_join(char **cmd, t_client *client, t_connect *server);
int 		cmd_part(char **cmd, t_client *client, t_connect *server);
int 		cmd_users(char **cmd, t_client *client, t_connect *server);
int 		cmd_names(char **cmd, t_client *client, t_connect *server);
int 		cmd_msg(char **cmd, t_client *client, t_connect *server);
int 		cmd_send_file(char **cmd, t_client *client, t_connect *server);
int 		cmd_accept_file(char **cmd, t_client *client, t_connect *server);
int 		cmd_quit(char **cmd, t_client *client, t_connect *server);
int 		cmd_help(char **cmd, t_client *client, t_connect *server);
int     	cmd_active(char **cmd, t_client *client, t_connect *server);
int 		cmd_other(char **cmd, t_client *client, t_connect *server);

#endif 		/* __FNC_PTRS__ */
