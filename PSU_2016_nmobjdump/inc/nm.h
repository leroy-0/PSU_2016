/*
** nm.h for nm in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Feb 19 17:32:33 2017 leroy_0
** Last update Sun Feb 19 17:32:34 2017 leroy_0
*/

#ifndef __NM_H_
#define __NM_H_

#include "objdump.h"

bool 		init_sym(t_data *data, unsigned int x);
void 		print_sym(t_data *data);
char		get_sym_type_section(t_data *data, unsigned int x);
char		get_sym_type_std(t_data *data, unsigned int x);

#endif	/* __NM_H_ */
