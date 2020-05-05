/*
** team.c for team in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 15:06:19 2017 yan
** Last update Sun Jul  2 12:23:07 2017 yan
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"zappy_team.h"
#include	"zappy_server.h"

t_team		*find_team(t_server *server, char *name)
{
  t_team	*back;

  back = server->team;
  while (back)
    {
      if (strcmp(back->name, name) == 0)
        return (back);
      back = back->next;
    }
  return (NULL);
}

int		add_team(t_server *server, char *name)
{
  t_team	*tmp;
  t_team	*create;

  if ((create = create_team(name)) == NULL)
    return (-1);
  tmp = server->team;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp == NULL)
    server->team = create;
  else
    tmp->next = create;
  return (0);
}

t_team		*create_team(char *name)
{
  t_team	*back;

  if ((back = malloc(sizeof(t_team))) == NULL)
    {
      fprintf(stderr, "Error: Malloc failed\n");
      return (NULL);
    }
  back->list = NULL;
  back->next = NULL;
  bzero(back->name, 256);
  strcpy(back->name, name);
  return (back);
}

int		count_players(t_team *team)
{
  int		count;
  t_list_player	*tmp;

  count = 0;
  tmp = team->list;
  while (tmp)
    {
      count++;
      tmp = tmp->next;
    }
  return (count);
}

int		count_teams(t_server *server)
{
  int		 back;
  t_team	*team;

  team = server->team;
  back = 0;
  while (team)
  {
    back++;
    team = team->next;
  }
  return (back);
}
