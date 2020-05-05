/*
** print.c for print in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:10:19 2017 leroy_0
** Last update Sat Feb 25 18:10:20 2017 leroy_0
*/

#include        "nm.h"

void 				print_sym_type(t_data *data, unsigned int x)
{
  char				type;

  type = get_sym_type_section(data, x);
  if (type == '?')
    type = get_sym_type_std(data, x);
  if (data->is64)
  {
  	if (ELF64_ST_BIND(data->sym[x].st_info) == STB_GLOBAL)
  		type = toupper(type);
  }
  else
  {
  	if (ELF32_ST_BIND(data->sym[x].st_info) == STB_GLOBAL)
    	type = toupper(type);
  }
  printf("%c ", type);
}

void 				print_all_sym(t_data *data, unsigned int y)
{
	if (data->sym[y].st_shndx != SHN_UNDEF)
	{
		if (data->is64 == true)
			printf("%016x ", (int)data->sym[y].st_value);
		else
			printf("%08x ", (int)data->sym[y].st_value);
	}
	else
	{
		if (data->is64 == true)
			printf("%16s ", "");
		else
			printf("%8s ", "");
	}
	print_sym_type(data, y);
	printf("%s\n", &data->symtab[data->sym[y].st_name]);
}

void 				print_sym(t_data *data)
{
	unsigned int 	y;

	y = 0;
	while (y < data->symsize)
	{
		if (data->sym[y].st_info != STT_FILE
			&& strcmp(&data->symtab[data->sym[y].st_name], "") != 0)
		{
			print_all_sym(data, y);
		}
		y++;
	}
}
