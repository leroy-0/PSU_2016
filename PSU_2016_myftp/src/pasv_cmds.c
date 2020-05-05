/*
** pasv_cmds.c for pasv_cmds in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun May 21 21:49:30 2017 leroy_0
** Last update Sun May 21 21:49:31 2017 leroy_0
*/

#include	"myftp.h"

bool 			exec_download(char **cmd, struct s_server *server,
	struct s_client *client)
{
	int 				fd;

	if (access(cmd[1], F_OK | R_OK) == -1)
	{
		send_str(client->fd, "550 Permission denied.\r\n");
    	return (false);
    }
	if (!check_path(client, cmd[1], cmd[1]))
		return (false);
    if ((fd = open(cmd[1], O_RDONLY)) == -1)
    	return (false);
    if (!get_new_fd(server, client))
    	return (false);
    if (!send_str(client->pasv_fd, get_result(fd)))
    	return (false);
    if (!send_str(client->fd, "226 Transfer complete.\r\n"))
    	return (false);
    if (close(client->pasv_fd) == -1)
		return (false);
	server->pasv_fd = -1;
    return (true);
}

bool 			cmd_download(char **cmd, struct s_server *server,
	struct s_client *client)
{
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if (!client->pasv_mod)
	{
		if (!send_str(client->fd, "425 Use PORT or PASV first.\r\n"))
			return (false);
		return (true);
	}
	if (!exec_download(cmd, server, client))
		return (false);
    client->pasv_mod = false;
	return (true);
}

bool					upload_file(struct s_server *server,
	struct s_client *client, char *path)
{
	char 				*buff;
	int 				fd;

	if ((fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0666)) == -1
		|| is_directory(path))
	{
		send_str(client->fd, "550 Permission denied.\r\n");
		return (false);
	}
	if (!send_str(client->fd, "150 Uploading file.\r\n"))
		return (false);
	if (!get_new_fd(server, client))
		return (false);
	while ((buff = get_next_line(client->pasv_fd)))
	{
		if (buff[strlen(buff) - 1] == '\r')
			buff[strlen(buff) - 1] = '\0';
		if (!send_str(fd, buff) || !send_str(fd, "\n"))
			return (false);
	}
	if (close(fd) == -1)
		return (false);
	return (true);
}

bool 			cmd_upload(char **cmd, struct s_server *server,
	struct s_client *client)
{
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if (!client->pasv_mod)
	{
		send_str(client->fd, "425 Use PORT or PASV first.\r\n");
		return (false);
	}
	if (!cmd[1])
	{
		send_str(client->fd, "550 Permission denied.\r\n");
		return (false);
	}
    if (!upload_file(server, client, cmd[1]) ||
    	!send_str(client->fd, "226 Transfer complete.\r\n") ||
    	close(client->pasv_fd) == -1)
    {
    	return (false);
    }
	server->pasv_fd = -1;
    client->pasv_mod = false;
	return (true);
}
