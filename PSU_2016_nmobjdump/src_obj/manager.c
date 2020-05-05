/*
** manager.c for manager in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:17:47 2017 leroy_0
** Last update Sat Feb 25 18:17:47 2017 leroy_0
*/

#include "objdump.h"

bool              init_ar(t_data *data)
{
  size_t          bytes;
  struct ar_hdr   arhdr;

  bytes = fread (&arhdr, 1, sizeof(arhdr), data->file);
  if (bytes != sizeof(arhdr))
    return (false);
  data->ar_size = strtoul(arhdr.ar_size, NULL, 10);
  data->filename = get_filename(arhdr.ar_name);
  data->ar_offset = ftell(data->file);
  if (data->filename && strcmp(data->filename, "//") == 0)
  {
    get_long_filenames(data, arhdr);
    data->filename[0] = '\0';
  }
  else
  {
    change_longname(data);
    if (isheader(data->filename) == false && !get_header(data))
      return (false);
  }
  return (true);
}

bool              init_file(t_data *data, char *filename)
{
  if (fseek(data->file, 0, SEEK_END) != 0)
    return (false);
  data->ar_size = ftell(data->file);
  if (fseek(data->file, 0, SEEK_SET) != 0)
    return (false);
  data->ar_offset = 0;
  data->filename = filename;
  if (!get_header(data))
    return (false);
  return (true);
}

t_data 			      *init_data(t_data *data, char *filename, bool archive)
{
  if (!data)
    if ((data = alloc_and_seek(filename, archive)) == NULL)
      return (NULL);

  if (archive)
  {
    if (init_ar(data) == false)
      return (NULL);
  }
  else
  {
    if (init_file(data, filename) == false)
      return (NULL);
  }
  return (data);
}

void      objdump_file(t_data *data, char *filename)
{
  if ((data = init_data(data, filename, false)) != NULL)
  {
    option_f(data);
    option_s(data);
    free(data->ehdr);
    free(data->shdr);
    free(data->tab);
    fclose(data->file);
  }
  if (data)
    free(data);
  data = NULL;
}

bool 			load_and_check(int nbargs, char **args)
{
  t_data 		*data;
  int 			x;

  x = 0;
  data = NULL;
  while (++x < nbargs)
    {
      if (check_archive(args[x]) == 0)
        objdump_ar(args[x]);
      else
        objdump_file(data, args[x]);
    }
  if (data)
    free(data);
  else
    return (false);
  return (true);
}
