/*
** input.c for input in /home/yan/Documents/psu/PSU_2016_myirc
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Thu Jun  1 15:43:11 2017 yan
** Last update Thu Jun  1 15:53:56 2017 yan
*/

#include	"common.h"
#include	"myirc.h"

t_input		*create_input(int fd)
{
  t_input	*back;

  if ((back = malloc(sizeof(t_input))) == NULL)
    {
      fprintf(stderr, "Error : input creation failed\n");
      return (NULL);
    }
  back->fd = fd;
  back->buffer = create_buffer();
  return (back);
}
