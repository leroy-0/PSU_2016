/*
** objdump_ar.c for objdump_ar in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:23:51 2017 leroy_0
** Last update Sat Feb 25 18:23:51 2017 leroy_0
*/

#include "objdump.h"

int     check_archive(char *filename)
{
  FILE  *file;
  char  ar_file[SARMAG];

  if ((file = fopen(filename, "rb")) == NULL)
    return (1);
  if (fread(ar_file, SARMAG, 1, file) != 1)
    return (1);
  fclose(file);
  return (memcmp(ar_file, ARMAG, SARMAG));
}

void      get_filename_root(char *src, char *dest)
{
  src++;
  if (*src == '/')
  {
    dest[0] = '/';
    dest[1] = '/';
    dest[2] = '\0';
  }
  else
  {
    while (*src && isdigit(*src) != 0)
      *dest++ = *src++;
    *dest = '\0';
  }
}

char			*get_filename(char *src)
{
	char 		*dest;
	char 		*save;

  dest = malloc(sizeof(char) * 4096);
  save = dest;
  if (!dest)
    return (NULL);
  if (*src && *src == '/')
    get_filename_root(src, dest);
  else
  {
 	  while (*src && *src != '/')
 	  	*dest++ = *src++;
    *dest = '\0';
  }
  if (strcmp(save, "") == 0)
  {
    free(dest);
    return (NULL);
  }
  return (save);
}

bool 	isheader(char *filename)
{
	if (!filename || filename[0] == '\0' || strcmp(filename, "") == 0)
		return (true);
	return (false);
}

void	objdump_ar(char *filename)
{
  t_data 		*data;

	data = NULL;
  while ((data = init_data(data, filename, true)) != NULL)
  {
  	if (isheader(data->filename) == false)
  	{
  		option_f(data);
  		option_s(data);
  		free(data->ehdr);
  		free(data->shdr);
  		free(data->tab);
  	}
  	if (fseek (data->file,
      (data->ar_offset + data->ar_size + (data->ar_size & 1)),
      SEEK_SET) != 0)
  	break;
  }
  if (data)
  {
    free_longnames(data);
	 	fclose(data->file);
  }
}
