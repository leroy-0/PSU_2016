/*
** objdump.c for objdump in /home/leroy_0/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <leroy_0@epitech.net>
** 
** Started on  Wed Feb 15 13:44:56 2017 leroy_0
** Last update Sun Feb 19 17:14:40 2017 leroy_0
*/

#include 	"objdump.h"

char 		*prog_name = "my_objdump";

void 				my_objdump(int nbargs, char **args)
{
	t_data 			*data;

	data = NULL;
	if (nbargs == 1)
	{
		if ((data = init_data(data, "a.out", false)) == NULL)
			return ;
		option_f(data);
		option_s(data);
        free(data->ehdr);
        free(data->shdr);
        free(data->tab);
        fclose(data->file);
	}
	else
		load_and_check(nbargs, args);
}

int             main(int ac, char **av)
{
	if ((prog_name = get_progname(av[0])) == NULL)
		return (1);
	my_objdump(ac, av);
	free(prog_name);
	return (0);
}
