/*
** tools3.c for tools3 in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Fri Jun  9 15:57:49 2017 yan
** Last update Fri Jun  9 16:29:47 2017 yan
*/

#include	<string.h>
#include	<stdlib.h>

void		free_tab(char ***cmd)
{
  int		a;

  a = 0;
  while ((*cmd)[a])
    {
      free((*cmd)[a]);
      a++;
    }
  free(*cmd);
}

void		remove_slash(char **cmd)
{
  char		*tmp;

  if (cmd && cmd[0])
    {
      if ((tmp = malloc(sizeof(char) * strlen(cmd[0]))) != NULL)
	{
	  if (cmd[0][0] == '/')
	    {
	      strcpy(tmp, cmd[0] + 1);
	      tmp[strlen(cmd[0]) - 1] = '\0';
	    }
	  else
	    {
	      strcpy(tmp, cmd[0]);
	      tmp[strlen(cmd[0])] = '\0';
	    }
	  free(cmd[0]);
	  cmd[0] = tmp;
	}
    }
}
