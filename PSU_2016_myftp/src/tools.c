/*
** tools.c for tools in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 18:22:07 2017 leroy_0
** Last update Thu May 18 18:22:08 2017 leroy_0
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "myftp.h"

bool 		is_digit(const char *nb)
{
	int 	x;

	x = 0;
	if (!nb)
		return (false);
	while (nb && nb[x])
	{
		if (!isdigit(nb[x]) && nb[x] != '.')
			return (false);
		x++;
	}
	return (true);
}

bool 			is_directory(const char *path)
{
   struct stat statbuf;

   if (stat(path, &statbuf) != 0)
       return (false);
   return (S_ISDIR(statbuf.st_mode));
}

bool 	send_str(int fd, const char *str)
{
	if (str)
		if (write(fd, str, strlen(str)) == -1)
			return (false);
	return (true);
}
