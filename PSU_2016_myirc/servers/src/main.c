/*
** main.c for main in /home/yan/Documents/psu/PSU_2016_myftp
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed May 10 14:08:02 2017 yan
** Last update Mon May 22 14:39:14 2017 yan
*/

#include	<stdlib.h>
#include	"myirc.h"

int		main(int argc, char **argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "Usage : %s port\n", argv[0]);
      return (1);
    }
    if (is_digit(argv[1]) == false)
    {
    	printf("%s\n", get_error(BAD_PORT));
    	return (1);
    }
  return (start_server(atoi(argv[1])));
}
