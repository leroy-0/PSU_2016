/*
** myirc.h for myirc in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Mon May 22 13:43:18 2017 yan
** Last update Wed Jun  7 22:56:22 2017 yan
*/

#ifndef 	_MY_IRC__
# define 	_MY_IRC__

# include		<netinet/in.h>
# include		<sys/types.h>
# include		<sys/socket.h>
# include 		<arpa/inet.h>
# include		<stdbool.h>
# include		<stdlib.h>
# include		<stdio.h>
# include		<unistd.h>
# include		<string.h>
# include		<stdio.h>
# include		"common.h"

typedef struct		s_connect
{
  struct sockaddr_in	s;
  int			fd;
  pthread_t		reader;
}			t_connect;

//client
t_connect		*create_client();
int			close_client(t_connect **client);
int			start_client();
t_connect		*init_client(in_addr_t ip, int port);
int			manage_commands(char *buffer, t_connect **client);

//send
bool			send_cmd(char **cmd, t_connect *client);

//tools
char			*epur_string(char *str);

#endif 		/* _MY_IRC__ */
