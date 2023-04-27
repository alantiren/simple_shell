#include "shell.h"

/**
 * print_enviro - Function to print the current program environment.
 * @env_point: Pointers array where are stored all the environment variables.
 * Return - void.
 */

void print_enviro(char **env_point)
{
	int i = 0;

	if (env_point)
	{
		while (env_point[i])
		{
			write(STDOUT_FILENO, env_point[i], str_len(env_point[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return;
	}
	perror("Unable to find envp.");
}
