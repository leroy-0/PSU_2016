/*
** parsing_args.c for parsing_args in /home/tekm/tek2/PSU_2016_zappy
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Jul  2 20:39:48 2017 leroy_0
** Last update Sun Jul  2 20:39:49 2017 leroy_0
*/

#include	<stdbool.h>
#include	<getopt.h>
#include	<memory.h>
#include        "zappy_parsing.h"

char		*recup_value(int argc, char **argv)
{
  char		*str;

  (void)(argc);
  optind--;
  str = strdup(argv[optind]);
  return (str);
}

char		**looping_function(char **name, bool mod, char **argv, int argc)
{
  int		i;

  i = 0;
  while (optind < argc && *argv[optind] != '-')
  {
    if (mod)
      name[i] = strdup(argv[optind]);
    i++;
    optind++;
  }
  if (mod)
    name[i] = NULL;
  if (!mod)
    name = malloc(sizeof(char *) * (i + 1));
  if (i == 0)
    return (NULL);
  return (name);
}

char		**recup_name_team(int argc, char **argv)
{
  char		**name;
  int		save;

  name = NULL;
  optind--;
  save = optind;
  if ((name = looping_function(name, false, argv, argc)) == NULL)
    return (NULL);
  optind = save;
  return (looping_function(name, true, argv, argc));
}

bool		*init_booleen_tab()
{
  int		i;
  bool		*tab;

  i = 0;
  tab = x_malloc(sizeof(bool) * 9);
  while (i < 9)
  {
    tab[i] = true;
    i++;
  }
  return (tab);
}

bool		*parse_all_arg(t_parse *parse, int argc, char **argv)
{
  bool		*tab;
  int		c;
  int		i;

  opterr = 0;
  i = 0;
  tab = init_booleen_tab();
  while ((c = getopt(argc, argv, "f:hp:x:y:n:c:")) != -1)
  {
    if (c == ERROR)
      parse->flags.error_flags++;
    while (parse->ptr_func[i].name != '\0' && parse->ptr_func[i].name != c)
      i++;
    if (parse->ptr_func[i].name != '\0' && parse->ptr_func[i].name == c)
      tab[i] = parse->ptr_func[i].ptr(parse, argv, argc);
    i = 0;
  }
  return (tab);
}
