/*
** server.c for server in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 18:16:55 2017 leroy_0
** Last update Thu May 18 18:16:55 2017 leroy_0
*/

#include "myftp.h"

int 	pid;

void 	zombie_hunter(int sig)
{
	(void)sig;
	int status;
    wait(&status);
}

void	run_server(struct s_server *server)
{
	struct 	s_client 	*client;

	while (1)
	{
		if ((client = init_client(server->fd)) == NULL)
		{
			printf("Error: Failed to initialize client\n");
			return;
		}
		if ((pid = fork()) == 0)
		{
			close(server->fd);
			if (!send_str(client->fd, "220 Connection established\r\n"))
				return;
			start_server(server, client);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (close(client->fd) == -1)
				return;
		}
	}
}

void 	launch_server(char *port, char *path)
{
	struct 	s_server 	*server;

	signal(SIGCHLD, zombie_hunter);
	if (is_digit(port) && is_directory(path))
	{
		chdir(path);
		path = getcwd(NULL, 0);
		if ((server = init_server(INADDR_ANY,
			ntohs(atoi(port)), path)) == NULL || !config_server(server))
		{
			printf("Error: Failed to start server\n");
			return;
		}
		run_server(server);
		if (close(server->fd) == -1)
			return;
	}
	else
	{
		printf("Error: Bad arguments\n");
		return;
	}
}

int 	main(int ac, char **av)
{
	if (ac == 3)
	{
		launch_server(av[1], av[2]);
	}
	else
	{
		printf("Usage : ./server port path\n");
		return (-1);
	}
	return (0);
}
