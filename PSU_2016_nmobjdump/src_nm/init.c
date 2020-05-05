/*
** print.c for init in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:09:08 2017 leroy_0
** Last update Sat Feb 25 18:09:10 2017 leroy_0
*/

#include        "nm.h"

void                fill_sym_members(t_data *data, Elf32_Sym *sym32)
{
  unsigned int      x;

  x = 0;
  while (x < data->symsize)
  {
    data->sym[x].st_name = sym32[x].st_name;
    data->sym[x].st_value = sym32[x].st_value;
    data->sym[x].st_size = sym32[x].st_size;
    data->sym[x].st_info = sym32[x].st_info;
    data->sym[x].st_other = sym32[x].st_other;
    data->sym[x].st_shndx = sym32[x].st_shndx;
    x++;
  }
}

bool 				copy_sym32(t_data *data, unsigned int x)
{
  Elf32_Sym        *sym32;

  sym32 = (Elf32_Sym *)get_data(data,
		data->shdr[x].sh_entsize * data->symsize,
		data->shdr[x].sh_offset,
		data->shdr[x].sh_entsize * data->symsize);
  if (!sym32)
    return (false);
  data->sym = malloc(data->shdr[x].sh_entsize
    * data->symsize * sizeof(Elf32_Sym));
  if (!data->sym)
    return (false);
  fill_sym_members(data, sym32);
  free(sym32);
  return (true);
}

bool 				init_sym(t_data *data, unsigned int x)
{
	data->symsize = data->shdr[x].sh_size / data->shdr[x].sh_entsize;
	if (data->is64)
	{
		data->sym = (Elf64_Sym *)get_data(data,
			data->shdr[x].sh_entsize * data->symsize,
			data->shdr[x].sh_offset,
			data->shdr[x].sh_entsize * data->symsize);
	}
	else
		copy_sym32(data, x);
	data->symtab = get_data(data,
			data->shdr[data->shdr[x].sh_link].sh_size,
			data->shdr[data->shdr[x].sh_link].sh_offset,
			data->shdr[data->shdr[x].sh_link].sh_size);
	return (true);
}
