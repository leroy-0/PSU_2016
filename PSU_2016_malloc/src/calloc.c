/*
** calloc.c for Project-Master in /home/tekm/tek2/old_malloc/new_malloc/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Tue Feb  7 03:28:32 2017 leroy_0
** Last update Thu Feb  9 14:43:59 2017 Sebastien Bruere
*/

#include	"malloc.h"

void		*safe_calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if (nmemb == 0 || size == 0)
    return (NULL);
  ptr = safe_malloc(size * nmemb);
  bzero(ptr, align_size(size * nmemb));
  return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  pthread_mutex_lock(&(g_data.mutex));
  ptr = safe_calloc(nmemb, size);
  pthread_mutex_unlock(&(g_data.mutex));
  return (ptr);
}
