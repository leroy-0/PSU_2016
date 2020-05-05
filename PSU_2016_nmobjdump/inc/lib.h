/*
** lib.h for lib in /home/tekm/tek2/PSU_2016_nmobjdump
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Fri Feb 17 14:32:01 2017 leroy_0
** Last update Sun Feb 19 17:31:38 2017 leroy_0
*/

#ifndef __LIB_H_
#define __LIB_H_

#include        <ar.h>
#include        <elf.h>
#include        <ctype.h>
#include        <unistd.h>
#include        <stdio.h>
#include        <sys/stat.h>
#include        <fcntl.h>
#include        <sys/mman.h>
#include 		<stdlib.h>
#include 		<string.h>
#include 		<stdbool.h>

typedef	struct 	s_data
{
  Elf64_Ehdr       	*ehdr; //Elf64_Ehdr
  Elf64_Shdr       	*shdr; //Elf64_Shdr
  Elf64_Sym         *sym;
  unsigned int ar_size;
  unsigned int ar_offset;
  FILE      *file;
  struct stat	stats;
  unsigned int  symsize;
  char    *symtab;
  char    *filename;
  char 		*tab;
  bool     is64;
  char    **longnames;
}		t_data;

typedef struct	s_name
{
  uint16_t	value;
  char		*str;
}		t_name;

typedef enum	e_flags
  {
    BFD_NO_FLAGS	= 0,
    HAS_RELOC		= 1,
    EXEC_P		= 2,
    HAS_LINENO		= 4,
    HAS_DEBUG		= 8,
    HAS_SYMS		= 16,
    HAS_LOCAL		= 32,
    DYNAMIC		= 64,
    WP_TEXT		= 128,
    D_PAGED		= 256
  }				t_flags;

bool 		get_header(t_data *data);
char		*get_progname(char *filename);
char		*get_architecture(t_name *type, uint8_t id);
void    print_architecture(t_data *data);
void    print_format(t_data *data);
void    *get_data(t_data *data, int to_malloc, int offset, int size);
bool    choose_version_header(t_data *data);
bool    malloc_and_read32(t_data *data);
bool    malloc_and_read64(t_data *data);
bool    fill_ehdr32(t_data *data);
bool    fill_shdr32(t_data *data);
int     check_64bits(t_data *data);

extern char 	*prog_name;

# define _PRINT_TYPE(flag, type, ret) \
printf("%s%s", ret && (flag & type) ? ", " : "", flag & type ? #type : "")

#endif		/* __LIB_H_ */
