/*
** print.c for print in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:26:44 2017 leroy_0
** Last update Sat Feb 25 18:28:45 2017 leroy_0
*/

#include "lib.h"

t_name machine[] =
  {
    {EM_NONE, "unknown"},
    {EM_SPARC, "sun"},
    {EM_386, "i386"},
    {EM_X86_64, "x86-64"},
    {EM_SPARC32PLUS, "sparcplus"},
    {EM_SPARCV9, "sparcv9"},
    {EM_IA_64, "ia64"},
    {0, NULL}
  };

t_name elfname[] =
  {
    {ELFCLASSNONE, "elf"},
    {ELFCLASS32, "elf32"},
    {ELFCLASS64, "elf64"},
    {0, NULL}
  };

t_name sysname[] =
  {
    {ELFOSABI_NETBSD, "netbsd"},
    {ELFOSABI_FREEBSD, "freebsd"},
    {ELFOSABI_LINUX, "linux"},
    {ELFOSABI_SOLARIS, "solaris"},
    {0, NULL}
  };

bool 			get_header(t_data *data)
{
  if (choose_version_header(data) == false)
    return (false);

  data->tab = (char *)get_data(data, sizeof(char) *
    data->shdr[data->ehdr->e_shstrndx].sh_size,
    data->shdr[data->ehdr->e_shstrndx].sh_offset,
    data->shdr[data->ehdr->e_shstrndx].sh_size);
  return (true);
}

char 				*get_progname(char *filename)
{
	char 			*str;
	unsigned int	x;
	unsigned int	z;

	if (!filename)
		return (NULL);
	x = strlen(filename) - 1;
	z = 0;
	while (x > 0)
	{
		if (filename[x] == '/')
			break;
		x--;
	}
	x++;
	str = malloc(sizeof(char) * (strlen(filename) - x + 1));
	if (!str)
		return (NULL);
	while (x <= strlen(filename))
	{
		str[z] = filename[x];
		z++;
		x++;
	}
	return (str);
}

char					*get_architecture(t_name *type, uint8_t id)
{
	unsigned int 		x;

	x = 0;
  	while (type && type[x].str)
  	{
  		if (type[x].value == id)
      		return (type[x].str);
    	x++;
  	}
  	return (NULL);
}

void    print_architecture(t_data *data)
{
  char  *str;

  str = get_architecture(machine, data->ehdr->e_machine);
  if (str && data->ehdr->e_machine == EM_X86_64)
    printf("i386:%s", get_architecture(machine, data->ehdr->e_machine));
  else if (str)
    printf("%s", get_architecture(machine, data->ehdr->e_machine));
}

void		print_format(t_data *data)
{
  char		*str;

  str = get_architecture(elfname, data->ehdr->e_ident[EI_CLASS]);
  if (str)
    printf("%s", str);
  str = get_architecture(machine, data->ehdr->e_machine);
  if (str)
    printf("-%s", str);
  str = get_architecture(sysname, data->ehdr->e_ident[EI_OSABI]);
  if (str)
      printf("-%s", str);
}
