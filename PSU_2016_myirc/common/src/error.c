/*
** error.c for error in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon May 22 17:45:30 2017 leroy_0
** Last update Tue May 30 17:07:11 2017 yan
*/

#include "common.h"

t_errors 		*init_errors()
{
  t_errors	 	*errors;

  if ((errors = malloc(sizeof(struct s_errors) * 9)) == NULL)
    return (NULL);
  errors[0].msg = "Fatal Error";
  errors[0].err = FATAL_ERROR;
  errors[1].msg = "Success";
  errors[1].err = SUCCESS;
  errors[2].msg = "Bad Arguments";
  errors[2].err = BAD_ARGUMENTS;
  errors[3].msg = "Client not connected";
  errors[3].err = NOT_CONNECTED;
  errors[4].msg = "Cannot connect to server";
  errors[4].err = BAD_CONNECTION;
  errors[5].msg = "Cannot open/read file";
  errors[5].err = FILE_FAIL;
  errors[6].msg = "Unknown command";
  errors[6].err = BAD_COMMAND;
  errors[7].msg = "Port isn't valid";
  errors[7].err = BAD_PORT;
  errors[8].msg = NULL;
  return (errors);
}

char 	      *get_error(int ret)
{
  t_errors 	*errors;
  char      *msg;
  int 	    x;

  if (ret == SUCCESS)
    return (NULL);
  x = 0;
  if (!(msg = malloc(sizeof(char) * 4096)))
    return (NULL);
  if ((errors = init_errors()) == NULL)
    return (NULL);
  while (errors[x].msg)
    {
      if (errors[x].err == ret)
      {
        sprintf(msg, "Command terminated with error code: %s.",
    errors[x].msg);
        return (msg);
      }
      x++;
    }
    return (NULL);
}
