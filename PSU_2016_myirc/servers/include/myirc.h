/*
** myirc.h for myirc in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Mon May 22 13:43:18 2017 yan
** Last update Fri Jun  9 19:59:08 2017 yan
*/

#ifndef _MY_IRC__
# define _MY_IRC__

# include		<stdbool.h>
# include		<stdlib.h>
# include		<stdio.h>
# include		<unistd.h>
# include		<string.h>
# include		<stdio.h>
# include		<sys/types.h>
# include		<sys/socket.h>
# include		<netinet/in.h>
# include		<time.h>
# include		"common.h"

struct			s_channel;

struct			s_file;

typedef struct		s_client
{
  int			fd;
  struct sockaddr_in	s;
  socklen_t		s_size;
  struct s_client	*next;
  char			*username;
  char			*nickname;
  char			*hostname;
  t_buffer		*buffer;
  struct s_channel	*active_channel;
  struct s_file		*file;
  bool			connected;
} t_client;

typedef struct		s_file
{
  char			*file;
  t_client		*client;
  struct s_file		*next;
} t_file;

typedef struct		s_name
{
  t_client		*user;
  struct s_name		*next;
} t_name;

typedef struct		s_channel
{
  char			*channel;
  t_name		*connected;
  struct s_channel	*next;
} t_channel;

typedef struct		s_connect
{
  struct sockaddr_in	s;
  int			fd;
  int			max_fd;
  fd_set		fds;
  t_client		*client;
  t_channel		*channel;
} t_connect;

int			start_server(int port);
int			create_client(t_connect *s);
t_buffer		*create_buffer();
bool			check_client(t_connect *data, char *name);
int			get_max_fd(t_connect *s);
void			set_bits(t_connect *s);
int			check_client_states(t_connect *s);
t_node			*new_node(char *buff, t_node *prev);
t_client		*find_client(t_connect *data, char *name);
t_channel		*create_channel(t_connect *server, char *name);
int			delete_from_channel(t_channel *, t_client *);
void			delete_from_channels(t_connect *, t_client *);
void			delete_client(t_connect *data, t_client *kill);
t_channel		*find_channel(t_connect *data, char *name);
t_name			*new_user(t_channel *channel, t_client *a);
void			cmd_info_curent(t_connect *server);
bool			check_func(t_client *, bool, char **, int);
bool			check_channel(char **cmd, t_client *client);
t_client		*find_client_in_channel(t_channel *channel, char *username);
int			manage_commands(char *buffer, t_client *, t_connect *);
int			execute_client(t_client *a, t_connect *s);
void			send_msg(char *username, int fd, char **cmd, int start);
void			send_to_all(t_channel *channel, char **cmd, char *username);
void			send_success(char *confirm, t_client *client);
void			send_success_own(char *confirm, t_client *client);

#endif  /* _MY_IRC__ */
