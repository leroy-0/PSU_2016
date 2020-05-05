/*
** manage_fd.c for manage_fd in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun May 21 18:57:33 2017 leroy_0
** Last update Sun May 21 18:57:45 2017 leroy_0
*/

#include	"myftp.h"

bool					manage_active_fd(struct s_server *server,
	struct s_client *client)
{
	struct s_server		*tmp_client;

	if ((tmp_client = init_server(inet_addr(server->act_ip),
		ntohs(server->act_port), server->home)) == NULL)
	{
		send_str(client->fd, "500 Illegal PORT command.\r\n");
		return (false);
	}
	if (!config_client(tmp_client))
	{
		send_str(client->fd, "425 Failed to establish connection.\r\n");
		return (false);
	}
	client->pasv_fd = tmp_client->fd;
	server->act_ip = NULL;
	server->act_port = -1;
	return (true);
}

bool					get_new_fd(struct s_server *server,
	struct s_client *client)
{
	struct 	s_client 	*pasv_client;

	if (server->act_ip == NULL)
    {
		if ((pasv_client = init_client(server->pasv_fd)) == NULL)
		{
			printf("Error: Failed to initialize client\n");
			return (false);
		}
		client->pasv_fd = pasv_client->fd;
	}
	else
	{
		if (!manage_active_fd(server, client))
			return (false);
	}
	return (true);
}
