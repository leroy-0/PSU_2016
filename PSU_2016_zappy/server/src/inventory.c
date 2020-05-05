/*
** inventory.c for inventory in /home/adrien/rendu/PSU_2016_zappy/server/src
** 
** Made by Adrien Bachelet
** Login   <adrien.bachelet@epitech.eu>
** 
** Started on  Thu Jun 22 13:59:39 2017 Adrien Bachelet
** Last update Thu Jun 29 16:50:15 2017 Bachelet
*/

#include	<memory.h>
#include	"zappy_server.h"

char		*add_element_inventory(char *inventory, int nb, char *name)
{
  char		tmp[15];

  inventory = my_add_to_str(inventory, name);
  sprintf(tmp, "%d", nb);
  inventory = my_add_to_str(inventory, tmp);
  return (inventory);
}
