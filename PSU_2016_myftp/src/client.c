/*
** client.c for client in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 18:15:59 2017 leroy_0
** Last update Thu May 18 18:16:00 2017 leroy_0
*/

#include "get_next_line.h"
#include "myftp.h"

void 		start_client(int fd)
{
	char 	*buff;

	while (buff)
	{
		if ((buff = get_next_line(fd)))
		{
			printf("%s\n", buff);
		}
		if ((buff = get_next_line(0)))
		{
			if (!send_str(fd, buff) || !send_str(fd, "\r\n"))
				return;
		}
	}
}

bool 	launch_client(const char *ip, const char *port)
{
	struct 	s_server 		*client;

	if (ip && is_digit(port))
	{
		if ((client = init_server(inet_addr(ip),
			ntohs(atoi(port)), "/home/")) == NULL)
		{
			printf("Error: Failed to initialize client\n");
			return (false);
		}
		if (!config_client(client))
		{
			printf("Error: Failed to connect to %s:%s\n", ip, port);
			return (false);
		}
		start_client(client->fd);
		if (close(client->fd) == -1)
			return (false);
	}
	else
	{
		printf("Error: Bad arguments\n");
		return (false);
	}
	return (true);
}

int 	main(int ac, char **av)
{
	if (ac == 3)
	{
		launch_client(av[1], av[2]);
	}
	else
	{
		printf("Usage : ./client ip port\n");
		return (-1);
	}
	return (0);
}
