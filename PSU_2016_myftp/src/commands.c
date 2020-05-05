/*
** commands.c for commands in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 18:22:19 2017 leroy_0
** Last update Thu May 18 18:22:20 2017 leroy_0
*/

#include 	"myftp.h"

bool 					set_pasv(struct s_client *client,
	struct s_server *tmp_serv)
{
	struct s_client 	*pasv_client;
	socklen_t 			size;
	char 				*msg;

	size = sizeof(tmp_serv->s_in);
	getsockname(tmp_serv->fd, (struct sockaddr *)&tmp_serv->s_in, &size);
	getpeername(tmp_serv->fd, (struct sockaddr *)&tmp_serv->s_in, &size);
	if ((msg = malloc(sizeof(char) * 4096)) == NULL)
		return (NULL);
	sprintf(msg, "227 Entering Passive Mode (%s,%d,%d)\r\n",
		change_letters(inet_ntoa(tmp_serv->s_in.sin_addr), '.', ','),
		ntohs(tmp_serv->s_in.sin_port) / 256,
		ntohs(tmp_serv->s_in.sin_port) % 256);
	if (!send_str(client->fd, msg))
		return (false);
	if ((pasv_client = init_client(tmp_serv->fd)) == NULL)
	{
		printf("Error: Failed to initialize client\n");
		return (false);
	}
	client->pasv_fd = pasv_client->fd;
	client->pasv_mod = true;
	return (true);
}

bool 		cmd_passive(char **cmd, struct s_server *server,
	struct s_client *client)
{
	struct s_server 	*tmp_serv;

	(void)cmd;
	(void)server;
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if ((tmp_serv = init_server(inet_addr("127.0.0.1"),
		0, server->home)) == NULL)
	{
		printf("Error: Failed to initialize server\n");
		return (false);
	}
	if (!config_server(tmp_serv))
	{
		printf("Error: Failed to configure server\n");
		return (false);
	}
	return (set_pasv(client, tmp_serv));
}

char 					*find_ip(struct s_client *client, char **tab)
{
	char 				*ip;
	int 				x;

	x = 0;
	if ((ip = malloc(sizeof(char) * 4096)) == NULL)
		return (NULL);
	while (tab[x])
	{
		if (x < 4)
		{
			if (x == 0)
				ip = strcpy(ip, tab[x]);
			else
			{
				ip = strcat(ip, ".");
				ip = strcat(ip, tab[x]);
			}
		}
		x++;
	}
	if (x != 6 && send_str(client->fd, "500 Illegal PORT command.\r\n"))
		ip = NULL;
	return (ip);
}

bool 					init_active(struct s_server *server,
	struct s_client *client, char *ip, int port)
{
	struct s_server		*tmp_client;

	if ((tmp_client = init_server(inet_addr(ip),
		ntohs(port), server->home)) == NULL)
	{
		send_str(client->fd, "500 Illegal PORT command.\r\n");
		return (false);
	}
	if (!send_str(client->fd, "200 PORT command successful.\r\n"))
		return (false);
	if (!config_client(tmp_client))
	{
		send_str(client->fd, "425 Failed to establish connection.\r\n");
		return (false);
	}
	client->pasv_fd = tmp_client->fd;
	client->pasv_mod = true;
	return (true);
}

bool 					cmd_port(char **cmd, struct s_server *server,
	struct s_client *client)
{
	char 				**tab;
	char 				*ip;
	int 				port;

	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if (!cmd[1])
	{
		send_str(client->fd, "500 Illegal PORT command.\r\n");
		return (false);
	}
	tab = my_strtab(cmd[1], ",");
	if ((ip = find_ip(client, tab)) == NULL)
		return (false);
	port = atoi(tab[4]) * 256 + atoi(tab[5]);
	return (init_active(server, client, ip, port));
}
