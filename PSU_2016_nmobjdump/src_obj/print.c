/*
** print.c for print in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sat Feb 25 18:18:16 2017 leroy_0
** Last update Sat Feb 25 18:18:17 2017 leroy_0
*/

#include "objdump.h"

void 		print_help()
{
  printf("Usage: %s <option(s)> <fichier(s)>\n", prog_name);
  printf("Afficher les informations depuis le(s) <fichier(s)> objet.\n");
  printf("Au moins un des commutateurs suivants doit être fourni :\n");
  printf("  -f, --file-headers");
  printf("\tAfficher le contenu global du fichier d'en-tête\n");
  printf("  -s, --full-contents");
  printf("\tAfficher le contenu complet de toutes les sections demandées\n");
}

void      print_flags(unsigned int flags)
{
  unsigned int     ret;

  ret = 0;
  if (flags == BFD_NO_FLAGS)
    printf("BFD_NO_PRINT_TYPELAGS");
  else
    {
      ret |= _PRINT_TYPE(flags, HAS_RELOC, ret);
      ret |= _PRINT_TYPE(flags, EXEC_P, ret);
      ret |= _PRINT_TYPE(flags, HAS_LINENO, ret);
      ret |= _PRINT_TYPE(flags, HAS_DEBUG, ret);
      ret |= _PRINT_TYPE(flags, HAS_SYMS, ret);
      ret |= _PRINT_TYPE(flags, DYNAMIC, ret);
      ret |= _PRINT_TYPE(flags, WP_TEXT, ret);
      ret |= _PRINT_TYPE(flags, D_PAGED, ret);
    }
  printf("\n");
}

void 		print_text(t_data *data, unsigned int y,
  unsigned int x, unsigned int row)
{
  uint8_t   *ret;
  unsigned int  delimit;

  delimit = y + 16;
  ret = (uint8_t *)get_data(data,
    sizeof(uint8_t) * data->shdr[x].sh_size,
    data->shdr[x].sh_offset, data->shdr[x].sh_size);
  while (y < delimit)
    {
      if (y < row)
      {
        if (ret[y] <= 126 && ret[y] >= 32)
          printf("%c", ret[y]);
        else
          printf(".");
      }
      else
        printf(" ");
      y++;
    }
  printf("\n");
  free(ret);
}

void		print_addr(t_data *data, unsigned int y,
  unsigned int x, unsigned int row)
{
  uint8_t 	*ret;
  unsigned int 	count;
  unsigned int 	delimit;

  count = 0;
  delimit = y + 16;
  ret = (uint8_t *)get_data(data, sizeof(uint8_t) * data->shdr[x].sh_size,
    data->shdr[x].sh_offset, data->shdr[x].sh_size);
  while (y < delimit)
    {
      if (y < row)
	printf("%02x", ret[y]);
      else
	printf("  ");
      count++;
      y++;
      if (count % 4 == 0)
	printf(" ");
    }
  printf(" ");
  free(ret);
}

void 		print_section(t_data *data, unsigned int x, unsigned int y)
{
  printf(" %04x ", (int)(data->shdr[x].sh_addr + y));
  if (y + 16 >= data->shdr[x].sh_size)
  {
    print_addr(data, y, x, data->shdr[x].sh_size);
    print_text(data, y, x, data->shdr[x].sh_size);
  }
  else
  {
    print_addr(data, y, x, y + 16);
    print_text(data, y, x, y + 16);
  }
}
