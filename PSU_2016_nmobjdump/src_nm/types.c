/*
** types.c for print in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:10:51 2017 leroy_0
** Last update Sat Feb 25 18:10:52 2017 leroy_0
*/

#include        "nm.h"

t_name types[] =
  {
    {'b', ".bss"},
    {'t', ".code"},
    {'t', ".fini_array"},
    {'d', ".data"},
    {'N', "*DEBUG*"},
    {'N', ".debug"},
    {'i', ".drectve"},
    {'e', ".edata"},
    {'t', ".fini"},
    {'i', ".idata"},
    {'t', ".init"},
    {'p', ".pdata"},
    {'r', ".rdata"},
    {'r', ".rodata"},
    {'s', ".sbss"},
    {'c', ".scommon"},
    {'g', ".sdata"},
    {'t', ".text"},
    {'d', "vars"},
    {'b', "zerovars"},
    {0, NULL}
  };

char		get_sym_type_std(t_data *data, unsigned int x)
{
  for (int i = 0; types[i].str; ++i)
   {
      if (&data->tab[data->shdr[data->sym[x].st_shndx].sh_name]
      	&& !strcmp(types[i].str,
      		&data->tab[data->shdr[data->sym[x].st_shndx].sh_name]))
		return (types[i].value);
   }
  if ((data->shdr[data->sym[x].st_shndx].sh_flags & SHF_EXECINSTR) != 0)
    return ('t');
  if ((data->shdr[data->sym[x].st_shndx].sh_flags & SHF_ALLOC)
  	&& (data->shdr[data->sym[x].st_shndx].sh_type != SHT_NOBITS))
    {
      if ((data->shdr[data->sym[x].st_shndx].sh_flags & SHF_WRITE) == 0)
	return ('r');
      else
	return ('d');
    }
  if (data->shdr[data->sym[x].st_shndx].sh_type == SHT_NOBITS)
    return ('b');
  if (data->shdr[data->sym[x].st_shndx].sh_type != SHT_NOBITS
  	&& (data->shdr[data->sym[x].st_shndx].sh_flags & SHF_WRITE) == 0)
    return ('n');
  return ('?');
}

char 		get_sym_type_section_param(t_data *data, unsigned int x,
	unsigned int elf_type, unsigned int elf_bind)
{
  if (data->sym[x].st_shndx == SHN_ABS)
    return ('a');
  if (data->sym[x].st_shndx == SHN_COMMON)
    return ('C');
  if (data->sym[x].st_shndx == SHN_UNDEF)
    {
      if (elf_bind == STB_WEAK)
        {
          if (elf_type == STT_OBJECT)
            return ('v');
          else
            return ('w');
        }
      else
        return ('U');
    }
  if (elf_bind == STB_WEAK)
    {
      if (elf_type == STT_OBJECT)
	return ('V');
      else
	return ('W');
    }
  return ('?');
}

char		get_sym_type_section(t_data *data, unsigned int x)
{
	unsigned int 	elf_type;
	unsigned int 	elf_bind;

	if (data->is64)
	{
		elf_type = ELF64_ST_TYPE(data->sym[x].st_info);
		elf_bind = ELF64_ST_BIND(data->sym[x].st_info);
	}
	else
	{
		elf_type = ELF32_ST_TYPE(data->sym[x].st_info);
		elf_bind = ELF32_ST_BIND(data->sym[x].st_info);
	}
	return (get_sym_type_section_param(data, x, elf_type, elf_bind));
}
