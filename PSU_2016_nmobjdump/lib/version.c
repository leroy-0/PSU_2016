/*
** version.c for version in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:27:46 2017 leroy_0
** Last update Sat Feb 25 18:27:54 2017 leroy_0
*/

#include "lib.h"

bool      malloc_and_read64(t_data *data)
{
  data->is64 = true;
  data->ehdr = (Elf64_Ehdr *)get_data(data,
    sizeof(Elf64_Ehdr), 0, sizeof(Elf64_Ehdr));
  if (!data->ehdr)
  {

    return (false);
  }
  data->shdr = (Elf64_Shdr *)get_data(data,
    sizeof(Elf64_Shdr) * data->ehdr->e_shnum,
    data->ehdr->e_shoff, data->ehdr->e_shentsize * data->ehdr->e_shnum);
  if (!data->shdr)
    return (false);
  return (true);
}

bool      malloc_and_read32(t_data *data)
{
  data->is64 = false;
  if (fill_ehdr32(data) == false)
    return (false);
  if (fill_shdr32(data) == false)
    return (false);
  return (true);
}

bool      choose_version_header(t_data *data)
{
  int     to_exec;

  to_exec = check_64bits(data);
  if (to_exec == 0)
  {
    if (malloc_and_read64(data) == false)
    {
      printf("%s: %s: File truncated\n", prog_name, data->filename);
      return (false);
    }
  }
  else if (to_exec == 1)
  {
    if (malloc_and_read32(data) == false)
    {
      printf("%s: %s: File truncated\n", prog_name, data->filename);
      return (false);
    }
  }
  else
  {
    printf("%s: %s: File format not recognized\n", prog_name, data->filename);
    return (false);
  }
  return (true);
}
