#include "shell.h"

/**
 * _taker - Function that takes a command and executes it using the execve
 * system call.
 *
 * @args: Array of arguments containing the command and its arguments.
 * @argsc: Number of arguments.
 * @env_point: Environment variables.
 * @wstatus: Exit status.
 *
 * Return: (void).
 */
void _taker(char **args, int argsc, char **env_point, int *wstatus)
{
	pid_t pid;
	int exe_stat;

	if (args[0] == NULL)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return;
	}

	if (pid == 0)
	{
		exe_stat = execve(args[0], args, env_point);
		if (exe_stat == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, wstatus, 0);
	}
}
