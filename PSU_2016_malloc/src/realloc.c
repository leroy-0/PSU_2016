/*
** realloc.c for Project-Master in /home/tekm/tek2/old_malloc/new_malloc/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Mon Feb  6 17:57:38 2017 leroy_0
** Last update Thu Feb  9 14:46:28 2017 Sebastien Bruere
*/

#include	"malloc.h"

void		*safe_realloc(void *ptr, size_t size)
{
  void		*new;
  size_t 	tmp_size;

  if ((int)size <= 0)
    safe_free(ptr);
  if ((int)size <= 0 || ptr == NULL)
    return (safe_malloc(size));
  tmp_size = ((t_malloc *)((void *)ptr - aligned_block()))->size;
  new = ((void *)ptr - aligned_block());
  if (size + aligned_block() > tmp_size)
    {
      new = safe_malloc(size);
      size = align_size(size);
      if (size <= tmp_size)
	memcpy(new, ptr, size);
      else
	memcpy(new, ptr, tmp_size);
      safe_free(ptr);
    }
  else
    new = (void *)((size_t)new + aligned_block());
  return (new);
}

void		*realloc(void *ptr, size_t size)
{
  t_malloc	*new;

  pthread_mutex_lock(&(g_data.mutex));
  new = safe_realloc(ptr, size);
  pthread_mutex_unlock(&(g_data.mutex));
  return (new);
}
