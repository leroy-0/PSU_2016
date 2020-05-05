/*
** block.c for Project-Master in /home/tekm/tek2/old_malloc/new_malloc/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Mon Feb  6 18:17:43 2017 leroy_0
** Last update Thu Feb  9 15:04:08 2017 Sebastien Bruere
*/

#include "malloc.h"

t_malloc      *get_block(size_t size)
{
  t_malloc    *tmp;

  tmp = g_data.first_block;
  while (tmp && g_data.last)
    {
      if (tmp->size >= size && tmp->used == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

void          *organise_block(t_malloc *tmp, size_t size)
{
  t_malloc    *new;

  if (tmp->size > size
      && tmp->size - size > aligned_block() + DEFAULT_BLOCK)
    {
      new = (void *)tmp + size;
      new->size = tmp->size - size;
      new->used = 0;
      new->prev = tmp;
      new->next = tmp->next;
      tmp->next = new;
      tmp->size = size;
      if (new->next)
	new->next->prev = new;
    }
  tmp->used = 1;
  return (tmp);
}

size_t 		manage_pagination(size_t size)
{
  size_t 	to_add;

  to_add = ((size / PAGESIZE) + 1) * PAGESIZE;
  if (g_data.last_block == NULL)
    {
      g_data.last_block = sbrk(0);
      if (g_data.last_block == (void *)-1)
        return ((size_t)-1);
      g_data.first_block = g_data.last_block;
    }
  if (sbrk(to_add) == (void *)-1)
    return ((size_t)-1);
  return (to_add);
}

void		*init_struct(size_t size)
{
  t_malloc 	*new;

  new = g_data.last_block;
  new->size = size;
  new->used = 1;
  new->next = NULL;
  new->prev = g_data.last;
  if (g_data.last)
    g_data.last->next = new;
  g_data.last = new;
  g_data.last_block = (void *)new + size;
  return (new);
}

void		    *new_block(size_t size)
{
  void		  *cur_brk;
  void		  *node_brk;
  size_t    ret_size;

  if (g_data.pagesize < size)
  {
    if ((ret_size = manage_pagination(size)) == (size_t)-1)
      return (NULL);
    g_data.pagesize += ret_size;
  }
  else
    {
      if ((cur_brk = sbrk(0)) == (void *)-1)
        return (NULL);
      node_brk = (void *)((void *)g_data.last_block + g_data.pagesize);
      if (cur_brk != node_brk)
	{
	  g_data.last_block = cur_brk;
	  g_data.pagesize = manage_pagination(size);
	}
    }
  g_data.pagesize -= size;
  return (init_struct(size));
}
