/*
** nm.c for nm in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:16:38 2017 leroy_0
** Last update Sat Feb 25 18:16:39 2017 leroy_0
*/

#include        "nm.h"

char 		*prog_name = "my_nm";

bool 				my_nm_file(t_data *data, bool showname)
{
	bool 			symbol;
	int 			x;

	x = 0;
	symbol = false;
	if (showname)
		printf("\n%s:\n", data->filename);
	while (x < data->ehdr->e_shnum)
	{
		if (data->shdr[x].sh_type == SHT_SYMTAB)
		{
			init_sym(data, x);
			print_sym(data);
			symbol = true;
		}
		x++;
	}
	if (!symbol)
		printf("%s: %s: no symbols\n", prog_name, data->filename);
	return (true);
}

void	 			my_nm_ar(char *filename)
{
  t_data 		*data;

  data = NULL;
  while ((data = init_data(data, filename, true)) != NULL)
  {
  	if (isheader(data->filename) == false)
  	{
 		my_nm_file(data, true);
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

bool	 			load_and_check_nm(int nbargs, char **args)
{
	t_data 			*data;
	int 			x;

	x = 0;
	data = NULL;
	while (++x < nbargs)
	{
		if (check_archive(args[x]) == false)
			my_nm_ar(args[x]);
		else
		{
			if ((data = init_data(data, args[x], false)) != NULL)
			{
				my_nm_file(data, false);
				free(data->ehdr);
  				free(data->shdr);
	  			free(data->tab);
		  		fclose(data->file);
		  	}
		}
	}
	return (true);
}

void 				my_nm(int nbargs, char **args)
{
	t_data 			*data;

	data = NULL;
	if (nbargs == 1)
	{
		if ((data = init_data(data, "a.out", false)) == NULL)
			return ;
		my_nm_file(data, false);
        free(data->ehdr);
        free(data->shdr);
        free(data->tab);
        fclose(data->file);
	}
	else
		load_and_check_nm(nbargs, args);
}

int             main(int ac, char **av)
{
	if ((prog_name = get_progname(av[0])) == NULL)
		return (1);
	my_nm(ac, av);
	free(prog_name);
	return (0);
}
