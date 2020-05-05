/*
** usage.c for usage in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Tue Jun 20 12:49:12 2017 Adrien Bachelet
** Last update Sun Jul  2 20:42:42 2017 leroy_0
*/

#include	<stdio.h>

int		usage()
{
  fprintf(stderr, "USAGE :./zappy_server -p port -x width -y height -n name1");
  fprintf(stderr, "name2 ... -c clientNb -f freq\n");
  fprintf(stderr, "\tport\tis the port number\n");
  fprintf(stderr, "\twidth\tis the width of the world\n");
  fprintf(stderr, "\theight\tis the height of the world\n");
  fprintf(stderr, "\tnameX\tis the name of the team X\n");
  fprintf(stderr, "\tclientNB\tis the number of "
	  "authorized clients per team\n");
  fprintf(stderr, "\tfreq\tis the reciprocal of time unit for execution of ");
  fprintf(stderr, "actions\n");
  return (0);
}
