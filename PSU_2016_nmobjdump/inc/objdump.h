/*
** objdump.h for objdump in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Feb 19 17:31:59 2017 leroy_0
** Last update Sun Feb 19 17:32:14 2017 leroy_0
*/

#ifndef __OBJDUMP_H_
#define __OBJDUMP_H_

#include "lib.h"

//PRINT
void 		print_help();
void 		print_text(t_data *data, unsigned int y,
	unsigned int x, unsigned int row);
void		print_addr(t_data *data, unsigned int y,
	unsigned int x, unsigned int row);
unsigned int 	diff_value(t_data *data, unsigned int x, unsigned int y);
void 		print_section(t_data *data, unsigned int x, unsigned int y);

//OPTIONS
void		option_s(t_data *data);
void		option_f(t_data *data);

//MANAGER
t_data 		*init_data(t_data *data, char *filename, bool archive);
bool 		manage_options(int nbargs, char **args, t_data *data);
bool 		load_and_check(int nbargs, char **args);

//FLAGS
unsigned int		get_flags(t_data *data);
void				print_flags(unsigned int flags);

//TOOLS
bool            get_long_filenames(t_data *data, struct ar_hdr arhdr);
void            change_longname(t_data *data);
t_data          *alloc_and_seek(char *filename, bool archive);
void    		free_longnames(t_data *data);

//AR
int     	check_archive(char *filename);
void		objdump_ar(char *filename);
char		*get_filename(char *src);
char 		*get_specific_filename(char *src);
bool 		isheader(char *filename);
void    	free_longnames(t_data *data);

#endif	/* __OBJDUMP_H_ */
