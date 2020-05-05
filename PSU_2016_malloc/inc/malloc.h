/*
** malloc.h for Project-Master in /home/tekm/tek1/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Tue Jan 24 11:15:50 2017 leroy_0
** Last update Thu Feb  9 14:52:01 2017 Sebastien Bruere
*/

#ifndef __MALLOC_H_
#define __MALLOC_H_

#define			PAGESIZE 	(int)(4096)
#define			DEFAULT_BLOCK	(16)

#include		<unistd.h>
#include		<stddef.h>
#include		<stdio.h>
#include		<stdbool.h>
#include		<string.h>
#include		<pthread.h>

typedef struct		s_malloc
{
  	char		used;
  	size_t		size;
	struct s_malloc	*next;
	struct s_malloc *prev;
}			t_malloc;

typedef struct 		s_data
{
	t_malloc 	*last;
	size_t 		pagesize;
	void 		*first_block;
	void 		*last_block;
	pthread_mutex_t mutex;
}			t_data;

extern 	t_data		g_data;

//LIBRARY
void		my_putchar(char);
void		my_putstr(char *);
void		my_putnbr(size_t);
void		print_hexa(unsigned long int nb, unsigned long int len);
void		print_hex(void *);

//TOOLS
size_t		align_size(size_t size);
size_t 		aligned_block();

//BLOCK
void 		*new_block(size_t size);
void		*organise_block(t_malloc *tmp, size_t size);
t_malloc	*get_block(size_t size);

//MAIN FUNCTIONS
void		safe_free(void *ptr);
void		*safe_malloc(size_t size);

void 		*realloc(void *ptr, size_t size);
void 		*malloc(size_t size);
void		free(void *ptr);
void		show_alloc_mem();

#endif	/* __MALLOC_H_ */
