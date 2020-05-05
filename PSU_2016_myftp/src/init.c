/*
** init.c for init in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 18:16:29 2017 leroy_0
** Last update Thu May 18 18:16:30 2017 leroy_0
*/

#include <string.h>
#include "get_next_line.h"
#include "myftp.h"

struct s_client 		*init_client(int fd)
{
	struct 	s_client 	*client;

	if ((client = malloc(sizeof(struct s_client))) == NULL)
		return (NULL);

	client->s_in_size = sizeof(struct sockaddr_in);

	if ((client->fd = accept(fd, (struct sockaddr *)&client->s_in_client,
		&client->s_in_size)) == -1)
	{
		if (close(fd) == -1)
		{
			return (NULL);
		}
		return (NULL);
	}
	client->ip = inet_ntoa(client->s_in_client.sin_addr);
	client->username = "";
	client->passwd = "";
	client->run = true;
	client->logged = false;
	client->pasv_fd = -1;
	client->pasv_mod = false;
	return (client);
}

struct 	s_server 	 	*init_server(in_addr_t ip, int port, char *home)
{
	struct 	s_server 	*server;

	if ((server = malloc(sizeof(struct s_server))) == NULL)
		return (NULL);

	server->port = port;

	if (!(server->pe = getprotobyname("TCP")))
		return (NULL);
	if ((server->fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto)) == -1)
		return (NULL);

	server->s_in.sin_family = AF_INET;
	server->s_in.sin_port = port;
	server->s_in.sin_addr.s_addr = ip;
	server->act_ip = NULL;
	server->act_port = -1;
	server->home = home;
	return (server);
}

bool 	config_server(struct s_server *server)
{
	if (bind(server->fd, (const struct sockaddr *)&server->s_in,
		sizeof(server->s_in)) == -1)
	{
		if (close(server->fd) == -1)
		{
			return (false);
		}
		return (false);
	}

	if (listen(server->fd, MAX_CONNECTIONS) == -1)
	{
		if (close(server->fd) == -1)
		{
			return (false);
		}
		return (false);
	}
	return (true);
}

bool		config_client(struct s_server *client)
{
	int		real_t;

	real_t = time(NULL);
	while (connect(client->fd, (struct sockaddr *)&client->s_in,
			sizeof(client->s_in)) == -1)
	{
		if ((time(NULL) - real_t) >= TIMEOUT)
			return (false);
	}
	return (true);
}
