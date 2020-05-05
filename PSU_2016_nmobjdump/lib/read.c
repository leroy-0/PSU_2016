/*
** read.c for read in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:32:41 2017 leroy_0
** Last update Sat Feb 25 18:32:49 2017 leroy_0
*/

#include "lib.h"

void      *get_data(t_data *data, int to_malloc, int offset, int size)
{
  void    *ptr;

  ptr = malloc(to_malloc);
  if (!ptr)
    return (NULL);
  if (offset >= 0)
    if (fseek(data->file, data->ar_offset + offset, SEEK_SET) != 0)
      return (NULL);
  if (fread(ptr, size, 1, data->file) != 1)
    return (NULL);
  return (ptr);
}
