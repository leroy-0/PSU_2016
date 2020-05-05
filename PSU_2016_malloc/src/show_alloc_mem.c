/*
** show_alloc_mem.c for Project-Master in /home/tekm/tek2/old_malloc/new_malloc/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Mon Feb  6 17:57:27 2017 leroy_0
** Last update Thu Feb  9 14:46:45 2017 Sebastien Bruere
*/

#include	"malloc.h"

void		show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = g_data.first_block;
  my_putstr("break : ");
  print_hex(sbrk(0));
  my_putchar('\n');
  while (tmp != NULL && g_data.last)
    {
      print_hex(tmp + 1);
      my_putstr(" - ");
      print_hex((void *)(tmp + 1) + tmp->size - aligned_block());
      my_putstr(" : ");
      my_putnbr(tmp->size - aligned_block());
      if (tmp->used == 1)
	{
	  my_putstr(" bytes\n");
	}
      else
	my_putstr(" bytes are freed\n");
      tmp = tmp->next;
    }
}
