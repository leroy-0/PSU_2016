/*
** common.h for common in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 24 15:32:52 2017 leroy_0
** Last update Fri Jun  9 16:38:17 2017 yan
*/

#ifndef 	__COMMON__
# define 	__COMMON__

# include 	<stdbool.h>
# include 	<stdlib.h>
# include 	<stdio.h>
# include 	<string.h>
# include	<sys/socket.h>
# define	MAX_PATH	(4096)
# define 	TIMEOUT		(20)
# define	NAME_LENGTH	(1024)
# define	MAX_CHANNELS	(1024)
# define	NODE_NUM	(4096)

typedef enum 	e_errorm
{
	FATAL_ERROR = -1,
	SUCCESS = 0,
	BAD_ARGUMENTS = 1,
	NOT_CONNECTED = 2,
	EXIT = 3,
	BAD_CONNECTION = 4,
	FILE_FAIL = 5,
	BAD_COMMAND = 6,
	BAD_PORT = 7
} t_errorm;

typedef struct	s_errors
{
  char		*msg;
  enum e_errorm	err;
} t_errors;

typedef struct	s_node
{
  char		*buf;
  struct s_node	*next;
} t_node;

typedef struct	s_buffer
{
  t_node	*start;
  t_node	*end;
} t_buffer;

char		*get_error(int ret);
bool		strcmp_insensible(char *src, char *to_cmp);
char		**my_strtab(char *str, char *s);
bool		check_validity(char **buff);
char		*epur_str(char *str);
bool		check_connection(char *line, char **ip, char **port);
bool		is_ip(const char *ip);
bool		is_digit(const char *nb);
int		send_message(int fd, char *messsage);
bool		strcmp_contain_insensible(char *str, char *to_cmp);
void		remove_slash(char **cmd);
void		free_tab(char ***cmd);
char    	*circular_buff(t_buffer *buffer, int fd, int *status);
char      	*get_cmd(t_buffer *buffer);

#endif			/* __COMMON__ */
