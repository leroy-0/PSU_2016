/*
** pwd_quit_delete.c for pwd_quit_delete in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 19:44:39 2017 leroy_0
** Last update Thu May 18 19:44:47 2017 leroy_0
*/

#include	"myftp.h"

bool 		cmd_pwd(char **cmd, struct s_server *server,
	struct s_client *client)
{
	char 	*msg;

	(void)cmd;
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if ((msg = malloc(sizeof(char) * (strlen(server->home)
		+ strlen("257 \"") + strlen("\"\r\n") + 1))) == NULL)
		return (false);
	msg = strcpy(msg, "257 \"");
	msg = strcat(msg, server->home);
	msg = strcat(msg, "\"\r\n");
	if (!send_str(client->fd, msg))
		return (false);
	return (true);
}

bool 		cmd_disconnect(char **cmd, struct s_server *server,
	struct s_client *client)
{
	(void)server;
	(void)cmd;
	if (!send_str(client->fd, "221 Goodbye.\r\n"))
		return (false);
	if (close(client->fd) == -1)
	{
		printf("Impossible de close\n");
		return (false);
	}
	client->run = false;
	return (true);
}

bool 		try_to_remove(struct s_server *server, struct s_client *client,
	char *to_delete)
{
	int 	fd;

	(void)server;
	if ((fd = open(to_delete, O_WRONLY) == -1) || remove(to_delete) == -1)
    {
    	send_str(client->fd, "550 Permission denied.\r\n");
    	return (false);
    }
    if (close(fd) == -1)
    	return (false);
    return (true);
}

bool 		cmd_delete(char **cmd, struct s_server *server,
	struct s_client *client)
{
	if (!client->logged)
	{
		send_str(client->fd, "530 Please login with USER and PASS.\r\n");
		return (false);
	}
	if (!cmd[1])
	{
		send_str(client->fd, "550 Permission denied.\r\n");
		return (false);
	}
	if (!try_to_remove(server, client, cmd[1]))
		return (false);
    if (!send_str(client->fd, "250 Deleting the file.\r\n"))
    {
    	return (false);
    }
	return (true);
}
