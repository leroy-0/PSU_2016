/*
** myftp.h for myftp in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 19:51:09 2017 leroy_0
** Last update Thu May 18 19:51:09 2017 leroy_0
*/

#ifndef __MYFTP_H_
#define __MYFTP_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <netdb.h>

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "get_next_line.h"

struct 					s_server
{
	struct protoent		*pe;
	struct sockaddr_in	s_in;
	char 				*home;
	int 				port;
	int 				fd;
	int 				pasv_fd;
	char 				*act_ip;
	int 				act_port;
};

struct 					s_client
{
	struct 	sockaddr_in s_in_client;
	socklen_t			s_in_size;
	char 				*ip;
	char 				*username;
	char 				*passwd;
	int 				fd;
	int 				pasv_fd;
	bool 				pasv_mod;
	bool 				logged;
	bool 				run;
};

struct					s_cmd
{
  bool          		(*func)(char **cmd, struct s_server *server,
  	struct s_client *client);
  char					*cmd;
};

//TOOLS
bool 					is_digit(const char *nb);
bool 					is_directory(const char *path);
bool	 				send_str(int fd, const char *str);
struct s_cmd			*init_ptrs();
char					*epur_str(char *str);

//TOOLS ANALYSE
char           			**my_strtab(char *str, char *s);
bool     				strcmp_insensible(char *src, char *to_cmp);

//TOOLS CMDS
char 					*find_variable(char *to_find, char *res);
char 					*find_in_env(char *to_find);
char					*change_letters(char *str, char find, char replace);
bool 					get_relative_path(char **home, char *to_search,
	char *save);

//TOOLS EXEC
char 					**prepare_args(char **cmd, struct s_server *server);
bool        			exec_cmd(char *args[4], int fd);

//CDUP CWD
bool					check_path(struct s_client *client, char *path,
	char *name);

//PASV CMD
bool					get_new_fd(struct s_server *server,
	struct s_client *client);

//SERVER
struct 	s_server 	 	*init_server(in_addr_t ip, int port, char *home);
bool 					config_server(struct s_server *server);
void					start_server(struct s_server *server,
	struct s_client *client);
struct s_client 		*init_client(int fd);
bool					config_client(struct s_server *client);

//TOOLS COMMANDS
char 					*get_result(int fd_pipe);

//COMMANDS
bool 		cmd_user(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_pass(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_cwd(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_cdup(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_disconnect(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_delete(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_pwd(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_passive(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_port(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_help(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_noop(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_download(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_upload(char **cmd, struct s_server *server,
	struct s_client *client);
bool 		cmd_list(char **cmd, struct s_server *server,
	struct s_client *client);

#define 	MAX_CONNECTIONS 	(420)
#define 	TIMEOUT 			(20)
#define 	LOGIN_U				"Anonymous"
#define 	LOGIN_P				""

#endif	/* __MYFTP_H_ */
