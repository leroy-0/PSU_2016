/*
** auth_and_basic.c for auth_and_basic in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 19:38:20 2017 leroy_0
** Last update Thu May 18 19:38:32 2017 leroy_0
*/

#include	"myftp.h"

bool 		cmd_help(char **cmd, struct s_server *server,
	struct s_client *client)
{
	char 	*msg;
	int 	fd;

	(void)cmd;
	(void)server;
	if (!client->logged)
	{
		send_str(client->fd, "530 Please login with USER and PASS.\r\n");
		return (false);
	}
	if (!send_str(client->fd, "214-The following commands are recognized\r\n"))
		return (false);
	if ((fd = open("help", O_RDONLY)) == -1)
		msg = "Unable to open help file.\r\n";
	else
	{
		if ((msg = get_result(fd)) == NULL)
			return (false);
		if (!send_str(client->fd, msg))
			return (false);
		close(fd);
	}
	if (!send_str(client->fd, "214 Help OK.\r\n"))
		return (false);
	return (true);
}

char 		*get_result(int fd_pipe)
{
	char 	buffer[4096];
	char 	*save;
	char 	*msg;
	int  	r;

	r = 0;
	msg = NULL;
	while ((r = read(fd_pipe, buffer, sizeof(buffer))) != 0)
    {
    	buffer[r] = '\0';
    	if (msg)
    	{
    		save = strdup(msg);
    		if ((msg = malloc(sizeof(char) *
    			(strlen(buffer) + strlen(msg) + 1))) == NULL)
    			return (NULL);
    		msg = strcpy(msg, save);
    		msg = strcat(msg, buffer);
    		free(save);
    	}
    	else
    		msg = strdup(buffer);
    }
	return (msg);
}

bool 		cmd_noop(char **cmd, struct s_server *server,
	struct s_client *client)
{
	(void)cmd;
	(void)server;
	if (!client->logged)
	{
		if (!send_str(client->fd, "530 Please login with USER and PASS.\r\n"))
			return (false);
		return (true);
	}
	if (!send_str(client->fd, "200 NOOP ok.\r\n"))
		return (false);
	return (true);
}

bool 		cmd_user(char **cmd, struct s_server *server,
	struct s_client *client)
{
	(void)server;
	if (client->logged)
	{
		if (!send_str(client->fd, "530 Can't change from guest user.\r\n"))
			return (false);
	}
	else
	{
		if (cmd[1])
		{
			client->username = strdup(epur_str(cmd[1]));
			if (!send_str(client->fd, "331 Please specify the password.\r\n"))
				return (false);
		}
		else
		{
			if (!send_str(client->fd, "530 Permission denied.\r\n"))
				return (false);
		}
	}
	return (true);
}

bool 		cmd_pass(char **cmd, struct s_server *server,
	struct s_client *client)
{
	(void)cmd;
	(void)server;
	if (client->logged)
	{
		if (!send_str(client->fd, "230 Already logged in.\r\n"))
				return (false);
	}
	else
	{
		if (strcmp(client->username, LOGIN_U) != 0)
		{
			if (!send_str(client->fd, "530 Login incorrect.\r\n"))
				return (false);
		}
		else
		{
			client->logged = true;
			if (!send_str(client->fd, "230 Login successful.\r\n"))
				return (false);
		}
	}
	return (true);
}
