/*
** list.c for list in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 19:41:18 2017 leroy_0
** Last update Thu May 18 19:41:27 2017 leroy_0
*/

#include	"myftp.h"

bool 		exec_ls(char **cmd, struct s_server *server,
	struct s_client *client)
{
	char 	**args;

	if ((args = prepare_args(cmd, server)) == NULL)
		return (false);
	if (!exec_cmd(args, client->pasv_fd))
	{
		send_str(client->fd, "550 Permission denied.\r\n");
		return (false);
	}
    if (!send_str(client->fd, "226 Directory send OK.\r\n")
    	|| close(client->pasv_fd) == -1)
    	return (false);
    return (true);
}

bool 		cmd_list(char **cmd, struct s_server *server,
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
	if (!send_str(client->fd, "150 Here comes the directory listing.\r\n"))
	    return (false);
	if (!get_new_fd(server, client))
		return (false);
    if (!exec_ls(cmd, server, client))
    {
    	return (false);
    }
    client->pasv_mod = false;
	return (true);
}
