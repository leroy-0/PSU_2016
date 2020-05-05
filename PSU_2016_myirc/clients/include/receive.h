/*
** receive.h for receive in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon Jun  5 16:43:14 2017 leroy_0
** Last update Wed Jun  7 16:57:07 2017 yan
*/

#ifndef __RECEIVE_H__
#define __RECEIVE_H__

#include  <time.h>
#include  <pthread.h>

//receive
void		*read_stdin(void *);
t_connect   *create_client(in_addr_t ip, int port);

#endif		/* __RECEIVE_H__ */
