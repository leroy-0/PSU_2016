/*
** fill.c for fill in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:35:47 2017 leroy_0
** Last update Sat Feb 25 18:35:48 2017 leroy_0
*/

#include "lib.h"

int             check_64bits(t_data *data)
{
  Elf32_Ehdr    ehdr;

  if (fseek(data->file, 0 + data->ar_offset, SEEK_SET) != 0)
    return (-1);
  if (fread(&ehdr, EI_NIDENT, 1, data->file) != 1)
    return (-1);
  if (ehdr.e_ident[EI_CLASS] == ELFCLASS64)
    return (0);
  else if (ehdr.e_ident[EI_CLASS] == ELFCLASS32)
    return (1);
  return (-1);
}

void                fill_shdr_members(t_data *data, Elf32_Shdr *shdr32)
{
  unsigned int      x;

  x = 0;
  while (x < data->ehdr->e_shnum)
  {
    data->shdr[x].sh_name = shdr32[x].sh_name;
    data->shdr[x].sh_type = shdr32[x].sh_type;
    data->shdr[x].sh_flags = shdr32[x].sh_flags;
    data->shdr[x].sh_addr = shdr32[x].sh_addr;
    data->shdr[x].sh_offset = shdr32[x].sh_offset;
    data->shdr[x].sh_size = shdr32[x].sh_size;
    data->shdr[x].sh_link = shdr32[x].sh_link;
    data->shdr[x].sh_info = shdr32[x].sh_info;
    data->shdr[x].sh_addralign = shdr32[x].sh_addralign;
    data->shdr[x].sh_entsize = shdr32[x].sh_entsize;
    x++;
  }
}

bool                fill_shdr32(t_data *data)
{
  Elf32_Shdr        *shdr32;

  shdr32 = (Elf32_Shdr *)get_data(data,
    sizeof(Elf32_Shdr) * data->ehdr->e_shnum,
    data->ehdr->e_shoff,
    data->ehdr->e_shentsize * data->ehdr->e_shnum);
  if (!shdr32)
    return (false);
  data->shdr = malloc(sizeof(Elf64_Shdr) * data->ehdr->e_shnum);
  if (!data->shdr)
    return (false);
  fill_shdr_members(data, shdr32);
  free(shdr32);
  return (true);
}

void                fill_ehdr_members(t_data *data, Elf32_Ehdr *ehdr32)
{
  int               x;

  x = -1;
  while (++x < EI_NIDENT)
    data->ehdr->e_ident[x] = ehdr32->e_ident[x];
  data->ehdr->e_type = ehdr32->e_type;
  data->ehdr->e_machine = ehdr32->e_machine;
  data->ehdr->e_version = ehdr32->e_version;
  data->ehdr->e_entry = ehdr32->e_entry;
  data->ehdr->e_phoff = ehdr32->e_phoff;
  data->ehdr->e_shoff = ehdr32->e_shoff;
  data->ehdr->e_flags = ehdr32->e_flags;
  data->ehdr->e_ehsize = ehdr32->e_ehsize;
  data->ehdr->e_phentsize = ehdr32->e_phentsize;
  data->ehdr->e_phnum = ehdr32->e_phnum;
  data->ehdr->e_shentsize = ehdr32->e_shentsize;
  data->ehdr->e_shnum = ehdr32->e_shnum;
  data->ehdr->e_shstrndx = ehdr32->e_shstrndx;
}

bool                fill_ehdr32(t_data *data)
{
  Elf32_Ehdr        *ehdr32;

  ehdr32 = (Elf32_Ehdr *)get_data(data,
    sizeof(Elf32_Ehdr), 0, sizeof(Elf32_Ehdr));
  if (!ehdr32)
    return (false);
  data->ehdr = malloc(sizeof(Elf64_Ehdr));
  if (!data->ehdr)
    return (false);
  fill_ehdr_members(data, ehdr32);
  free(ehdr32);
  return (true);
}
