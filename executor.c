#include "shell.h"

/**
 * _exetor - Function to execute a program in background.
 * @arr: (Array of pointers) wich contain the arguments
 * of the executed program.
 * @throgh: Contain the path where the program will be executed.
 * @s: Size of pointers array. (Array of pointers - **arr)
 * Return: Success (0), Program correctly executed and memory freed.
*/

int _exetor(char **arr, const char *throgh, int s)
{
	pid_t ch_ID = fork(), r_v = 0;
	int wstatus = 0;

	if (arr && throgh && s != 0)
	{
		if (ch_ID < 0)
		{
			perror("fork() error");
			return (-1);
		}

		if (ch_ID == 0)
		{
			r_v = execve(throgh, arr, NULL);
		}

		else
		{
			waitpid(ch_ID, &wstatus, 0);
		}

		if (r_v < 0)
		{
			printf("%s: %d: %s: not found\n", throgh, errno, arr[1]);
			/* execve() only returns on error */
			return (WEXITSTATUS(wstatus));
		}
		else
		{
			return (WEXITSTATUS(wstatus));
		}
	}
	perror("Executor can't find aop, path or size.");
	return (-1);
}
