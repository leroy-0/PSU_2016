/*
** tools.c for Project-Master in /home/tekm/tek2/old_malloc/new_malloc/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Mon Feb  6 18:01:08 2017 leroy_0
** Last update Thu Feb  9 14:46:54 2017 Sebastien Bruere
*/

#include	"malloc.h"

size_t		align_size(size_t size)
{
  size = (size + 3) & ~3;
  return (size);
}

size_t		aligned_block()
{
  size_t	size;

  size = align_size(2 * sizeof(t_malloc));
  return (size);
}
