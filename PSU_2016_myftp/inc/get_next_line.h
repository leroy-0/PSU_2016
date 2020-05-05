/*
** get_next_line.h for get_next_line in /home/leroy_0/rendu/CPE_2015_getnextline
**
** Made by leroy_0
** Login   <leroy_0@epitech.net>
**
** Started on  Mon Jan  4 09:50:22 2016 leroy_0
** Last update Fri Jan 15 12:34:14 2016 leroy_0
*/

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef READ_SIZE
# define READ_SIZE (14)
#endif /* !READ_SIZE */

char	*get_next_line(const int fd);
void    my_putstr(char *str);
int     my_strlen(char *str);

#endif /* !GET_NEXT_LINE_H */
