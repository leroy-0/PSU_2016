/*
** free.c for Project-Master in /home/tekm/tek2/old_malloc/new_malloc/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Mon Feb  6 17:57:32 2017 leroy_0
** Last update Thu Feb  9 14:44:25 2017 Sebastien Bruere
*/

#include		"malloc.h"

void 			delete_page(t_malloc *tmp)
{
  size_t 		to_delete;
  void			*cur_brk;

  if (tmp->prev)
    {
      tmp->prev->next = NULL;
      g_data.last = tmp->prev;
      g_data.last_block = (void *)g_data.last + g_data.last->size;
    }
  else
    {
      g_data.last_block = g_data.last;
      g_data.last = NULL;
    }
  g_data.pagesize += tmp->size;
  to_delete = g_data.pagesize / PAGESIZE;
  to_delete *= PAGESIZE;
  if ((cur_brk = sbrk(0)) == (void *)-1)
    return ;
  if (cur_brk == (void *)((void *)g_data.last_block + g_data.pagesize))
    sbrk(-to_delete);
  g_data.pagesize -= to_delete;
}

t_malloc		*organise_free(t_malloc *to_free)
{
  t_malloc		*tmp;

  tmp = g_data.first_block;
  while (tmp && tmp->next)
    {
      if (tmp->used == 0 && tmp->next->used == 0)
	{
	  tmp->size += tmp->next->size;
	  tmp->next = tmp->next->next;
	  if (tmp->next)
	    tmp->next->prev = tmp;
	  else
	    {
	      to_free = tmp;
	      break;
	    }
	}
      tmp = tmp->next;
    }
  g_data.last = tmp;
  return (to_free);
}

void			safe_free(void *ptr)
{
  t_malloc		*tmp;

  if (ptr == NULL)
    return ;
  tmp = (void *)ptr - aligned_block();
  if (ptr < g_data.first_block || ptr > g_data.last_block || tmp->used != 1)
    return ;
  tmp->used = 0;
  tmp = organise_free(tmp);
  if (tmp->next == NULL)
    delete_page(tmp);
}

void		free(void *ptr)
{
  pthread_mutex_lock(&(g_data.mutex));
  safe_free(ptr);
  pthread_mutex_unlock(&(g_data.mutex));
}
