/*
** options.c for options in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Feb 19 17:33:37 2017 leroy_0
** Last update Sun Feb 19 17:33:55 2017 leroy_0
*/

#include "objdump.h"

int     verify_section(t_data *data, unsigned int x)
{
  if (data->shdr[x].sh_size == 0)
    return (0);
  if (data->shdr[x].sh_type == SHT_NOBITS)
    return (0);
  if (data->shdr[x].sh_flags & SHF_ALLOC)
    return (1);
  if (data->shdr[x].sh_type == SHT_REL || data->shdr[x].sh_type == SHT_RELA)
    return (0);
  if (!strcmp(".stabstr", &(data->tab[data->shdr[x].sh_name])))
    return (1);
  if (data->shdr[x].sh_type == SHT_SYMTAB
    || data->shdr[x].sh_type == SHT_STRTAB)
    return (0);
  return (1);
}

void		option_s(t_data *data)
{
  unsigned int	x;
  unsigned int 	y;

  x = 0;
  while (x < data->ehdr->e_shnum)
    {
      if (verify_section(data, x) == 1)
	{
	  printf("Contents of section %s:\n",
		 &(data->tab[data->shdr[x].sh_name]));
	  y = 0;
	  while (y < data->shdr[x].sh_size)
	    {
	      print_section(data, x, y);
	      y += 16;
	    }
	}
      x++;
    }
}

void 		option_f(t_data *data)
{
  unsigned int		flags;

  printf("\n%s:     file format ", data->filename);
  print_format(data);
  printf("\n");
  flags = get_flags(data);
  printf("architecture: ");
  print_architecture(data);
  printf(", flags 0x%08x:\n", flags);
  print_flags(flags);
  if (data->is64)
    printf("start address 0x%016lx\n\n", data->ehdr->e_entry);
  else
    printf("start address 0x%08lx\n\n", data->ehdr->e_entry);
}
