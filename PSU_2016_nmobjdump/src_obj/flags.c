/*
** flags.c for flags in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Feb 24 01:01:14 2017 leroy_0
** Last update Fri Feb 24 01:01:15 2017 leroy_0
*/

#include "objdump.h"

bool			search_type(t_data *data, uint32_t type)
{
  unsigned int 	x;

  x = 0;
  while (x < data->ehdr->e_shnum)
    {
      if (data->shdr[x].sh_type == type)
	return (true);
      x++;
    }
  return (false);
}

unsigned int		get_flags(t_data *data)
{
  unsigned int		flags;

  flags = BFD_NO_FLAGS;
  if (search_type(data, SHT_REL) || search_type(data, SHT_RELA))
    flags |= HAS_RELOC;
  if (data->ehdr->e_type == ET_EXEC)
  {
    flags &= ~HAS_RELOC;
    flags |= EXEC_P | D_PAGED;
  }
  if (data->ehdr->e_type == ET_DYN)
  {
    flags &= ~HAS_RELOC;
    flags |= DYNAMIC | D_PAGED;
  }
  flags |= HAS_SYMS;
  return (flags);
}
