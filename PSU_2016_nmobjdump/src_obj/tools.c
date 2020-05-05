/*
** tools.c for tools in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:25:26 2017 leroy_0
** Last update Sat Feb 25 18:25:27 2017 leroy_0
*/

#include "objdump.h"

t_data            *alloc_and_seek(char *filename, bool archive)
{
  t_data          *data;

  if ((data = malloc(sizeof(t_data))) == NULL)
    return (NULL);
  if ((data->file = fopen(filename, "rb")) == NULL)
  {
    printf("%s: '%s': No such file\n", prog_name, filename);
    return (NULL);
  }
  if (archive)
  {
    if (fseek(data->file, SARMAG, SEEK_SET) != 0)
      return (NULL);
    printf("In archive %s:\n", filename);
  }
  data->longnames = NULL;
  return (data);
}

bool              copy_long_filenames(t_data *data,
  char *string_table, unsigned int y)
{
  unsigned int    x;

  x = 0;
  data->longnames = malloc(sizeof(char *) * (y + 1));
  if (!data->longnames)
    return (false);
  data->longnames[x] = strtok(string_table, "/\n");
  x++;
  while ((data->longnames[x++] = strtok(NULL, "/\n")) != NULL);
  return (true);
}

bool              get_long_filenames(t_data *data, struct ar_hdr arhdr)
{
  char          *string_table;
  unsigned int   size;
  unsigned int   x;
  unsigned int   y;

  x = 0;
  y = 0;
  size = strtoul(arhdr.ar_size, NULL, 10) - 2;
  string_table = malloc(size + 1);
  if (!string_table)
    return (false);
  if (fread(string_table, size, 1, data->file) != 1)
    return (false);
  string_table[size] = '\0';
  while (string_table && string_table[x])
  {
    if (string_table[x] == '/')
      y++;
    x++;
  }
  copy_long_filenames(data, string_table, y);
  return (true);
}

void                      change_longname(t_data *data)
{
  int                     x;
  bool                    longname;
  static unsigned int     i = 0;

  x = 0;
  longname = true;
  while (data->filename && data->filename[x])
  {
    if (isdigit(data->filename[x]) == 0)
      longname = false;
    x++;
  }
  if (isheader(data->filename) == false && longname == true && data->longnames)
  {
    free(data->filename);
    data->filename = data->longnames[i];
    i++;
  }
}

void    free_longnames(t_data *data)
{
  unsigned int x;

  x = 0;
  while (data->longnames && data->longnames[x])
  {
    free(data->longnames[x]);
    x++;
  }
}
