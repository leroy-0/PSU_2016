/*
** lib.c for Project-Master in /home/tekm/tek2/PSU_2016_malloc
** 
** Made by leroy_0
** Login   <leroy_0@epitech.eu>
** 
** Started on  Tue Jan 31 19:35:14 2017 leroy_0
** Last update Thu Feb  9 15:04:35 2017 Sebastien Bruere
*/

#include		<unistd.h>

void			my_putchar(char c)
{
  write(1, &c, 1);
}

void			my_putstr(char *str)
{
  unsigned long int	x;

  x = 0;
  while (str && str[x])
    my_putchar(str[x++]);
}

void			my_putnbr(long int n)
{
  if (n < 0)
    {
      my_putchar('-');
      n *= -1;
    }
  if (n > 9)
    {
      my_putnbr(n / 10);
      my_putnbr(n % 10);
    }
  else
    my_putchar(n + '0');
}

void			print_hexa(unsigned long int nb_to_convert,
				   unsigned long int len)
{
  char			hex_str[len];
  int			x;

  x = 0;
  while (nb_to_convert)
    {
      if (nb_to_convert % 16 >= 10)
	hex_str[x] = nb_to_convert % 16 + 'A' - 10;
      else
	hex_str[x] = nb_to_convert % 16 + '0';
      nb_to_convert /= 16;
      x++;
    }
  x--;
  my_putstr("0x");
  while (x >= 0)
    {
      my_putchar(hex_str[x]);
      x--;
    }
}

void			print_hex(void *ptr)
{
  unsigned long int	addr;
  int			size;

  size = 0;
  addr = (unsigned long int)ptr;
  while ((addr = addr/16))
    size++;
  print_hexa((unsigned long int)ptr, size);
}
