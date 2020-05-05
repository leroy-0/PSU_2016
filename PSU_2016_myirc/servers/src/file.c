/*
** file.c for file in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun  7 17:35:46 2017 yan
** Last update Wed Jun  7 17:46:59 2017 yan
*/

#include	"myirc.h"

int		add_file(t_connect *server, char *name, t_client *client)
{
  t_client	*tmp;

  tmp = server->client;
  while (tmp)
    {
      if (strcmp)
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return ();
  return (SUCCESS);
}

int		send_file(t_client *sender, t_client *receiver)
{
  return (SUCCESS);
}
