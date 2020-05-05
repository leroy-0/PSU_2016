/*
** tools_exec.c for tools_exec in /home/tekm/tek2/PSU_2016_myftp
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu May 18 19:50:26 2017 leroy_0
** Last update Thu May 18 19:50:26 2017 leroy_0
*/

#include	"myftp.h"

bool        exec_cmd(char *args[4], int fd)
{
    int pipefd[2];
    int status;

    pipe(pipefd);
    if (fork() == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        dup2(pipefd[1], 2);
        close(pipefd[1]);
        execv(args[0], args);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        close(pipefd[1]);
        if (!send_str(fd, get_result(pipefd[0])))
            return (false);
    }
    return (true);
}

char 		**prepare_args(char **cmd, struct s_server *server)
{
	char 	**args;

	if ((args = malloc(sizeof(char *) * 4)) == NULL)
		return (NULL);
	args[0] = "/bin/ls";
    if (cmd[1])
    	args[1] = cmd[1];
    else
    	args[1] = server->home;
    args[2] = "-all";
    args[3] = NULL;
    return (args);
}
