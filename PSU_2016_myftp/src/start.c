/*
** start.c for start in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed May 10 15:15:30 2017 leroy_0
** Last update Wed May 10 15:15:38 2017 leroy_0
*/

#include <string.h>
#include "get_next_line.h"
#include "myftp.h"

bool 				analyse_cmd(char **cmd, struct s_server *server,
	struct s_client *client)
{
	struct s_cmd 	*tab;
	int 			x;

	if (!cmd || !cmd[0])
		return (false);
	x = 0;
	tab = init_ptrs();
	while (tab && tab[x].cmd)
	{
		if (strcmp_insensible(tab[x].cmd, cmd[0]))
		{
			(tab[x].func)(cmd, server, client);
			return (true);
		}
		x++;
	}
	return (false);
}

bool 				check_validity(char **buff, struct s_client *client)
{
	unsigned int 	x;

	x = 0;
	if (strcmp(*buff, "") == 0)
		return (false);
	if ((*buff)[strlen(*buff) - 1] == '\r')
		(*buff)[strlen(*buff) - 1] = '\0';
	while (*buff && (*buff)[x])
	{
		if ((*buff)[x] == ' ')
			x++;
		else
			break;
	}
	if (!(strlen(*buff) == x && client->logged))
		*buff = epur_str(*buff);
	return (true);
}

void		start_server(struct s_server *server, struct s_client *client)
{
	char 	**tab;
	char 	*buff;

	while (client->run)
	{
		if ((buff = get_next_line(client->fd)))
		{
			if (check_validity(&buff, client))
			{
				tab = my_strtab(buff, " ");
				if (!analyse_cmd(tab, server, client))
				{
					if (!send_str(client->fd, "500 Unknown command.\r\n"))
						return;
				}
				free(tab);
			}
		}
		else
		{
			cmd_disconnect(NULL, server, client);
		}
	}
}
