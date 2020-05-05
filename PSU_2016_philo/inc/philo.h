/*
** philo.h for philo in /home/tekm/tek2/PSU_2016_philo
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Mar  9 08:31:25 2017 leroy_0
** Last update Thu Mar  9 08:31:26 2017 leroy_0
*/

#ifndef __PHILO_H_
#define __PHILO_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "extern.h"

typedef struct 		s_list
{
	bool			thinking;
	bool 			sleeping;
	bool 			chopstick;
	int 			eated;
	struct s_list 	*right;
	struct s_list 	*left;
}					t_list;

#define 	MAX_DURATION (10)

#define 	CAN_EAT(node) \
(node->right && node->right->chopstick == true \
	&& node->chopstick == true ? true : false)

#define 	CAN_THINK(node) \
(((node->right && node->right->chopstick == true \
	&& node->chopstick == false) \
	|| (node->right && node->right->chopstick == false \
	&& node->chopstick == true)) ? true : false)

#define 	CAN_SLEEP(node) \
(((node->thinking == true && CAN_EAT(node)) \
	|| node->thinking == false) ? true : false)

#endif /* __PHILO_H_ */