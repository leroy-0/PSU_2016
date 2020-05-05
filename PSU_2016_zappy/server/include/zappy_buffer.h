/*
** zappy_buffer.h for zappy_buffer in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Fri Jun 23 12:43:27 2017 yan
** Last update Fri Jun 23 16:06:12 2017 yan
*/

#ifndef			__ZAPPY_BUFFER__
# define		__ZAPPY_BUFFER__

typedef struct		s_buffer
{
  char			letter[4096];
  int			start;
  int			end;
} t_buffer;

t_buffer		*init_buffer();

# define		BUFFER_SIZE (500)

#endif /* __ZAPPY_BUFFER__ */
