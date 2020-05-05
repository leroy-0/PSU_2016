/*
** malloc.c for Project-Master in /home/tekm/tek1/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Tue Jan 24 10:12:01 2017 leroy_0
** Last update Thu Feb  9 14:54:52 2017 Sebastien Bruere
*/

#include "malloc.h"

t_data    g_data =
  {
    NULL,
    0,
    NULL,
    NULL,
    PTHREAD_MUTEX_INITIALIZER
  };

void          *safe_malloc(size_t size)
{
  t_malloc    *tmp;
  void        *ptr;

  if ((int)size >= 0)
    {
      size = align_size(size) + aligned_block();
      if ((tmp = get_block(size)) != NULL)
	ptr = organise_block(tmp, size);
      else
	ptr = new_block(size);

      if (ptr)
	ptr = (void *)((size_t)ptr + aligned_block());
      return (ptr);
    }
  return (NULL);
}

void		*malloc(size_t size)
{
  void		*ptr;

  pthread_mutex_lock(&(g_data.mutex));
  ptr = safe_malloc(size);
  pthread_mutex_unlock(&(g_data.mutex));
  return (ptr);
}
