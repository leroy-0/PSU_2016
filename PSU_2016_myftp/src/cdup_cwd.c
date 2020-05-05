/*
** cdup_cwd.c for cdup_cwd in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun May 21 21:35:30 2017 leroy_0
** Last update Sun May 21 21:35:30 2017 leroy_0
*/

#include	"myftp.h"

bool		change_dir(char **cmd, struct s_server *server,
	struct s_client *client)
{
	if (chdir(cmd[1]) == -1)
	{
		send_str(client->fd, "550 Failed to change directory.\r\n");
		return (NULL);
	}
	server->home = getcwd(NULL, 0);
	if (!send_str(client->fd, "250 Directory successfully changed.\r\n"))
		return (false);
	return (true);
}

bool			check_path(struct s_client *client, char *path, char *name)
{
	struct stat st;
	char 		*msg;

	if (path && stat(path, &st) == 0)
	{
		if ((msg = malloc(sizeof(char) * 4096)) == NULL)
			return (false);
		sprintf(msg,
			"150 Opening ASCII mode data connection for %s (%d bytes)\r\n",
			name, (int)st.st_size);
		if (!send_str(client->fd, msg))
			return (false);
		free(msg);
		return (true);
	}
	else
	{
		if (!send_str(client->fd, "550 Failed to open file.\r\n")
			|| close(client->pasv_fd) == -1)
			return (false);
	}
	return (false);
}

bool 		cmd_cwd(char **cmd, struct s_server *server,
	struct s_client *client)
{
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if (!cmd[1])
	{
		if (!send_str(client->fd, "550 Failed to change directory.\r\n"))
			return (false);
		return (true);
	}
	return (change_dir(cmd, server, client));
}

bool 		cmd_cdup(char **cmd, struct s_server *server,
	struct s_client *client)
{
	(void)cmd;
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	cmd[1] = "../";
	return (change_dir(cmd, server, client));
}
