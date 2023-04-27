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

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
        int i;
        size_t namelen = 0;

        if (name == NULL)
                return (NULL);

        /* Calculate the length of the name. */
        while (name[namelen])
                namelen++;

        /* Search the environment for the variable. */
        for (i = 0; environ[i] != NULL; i++)
        {
                /* Compare the first namelen characters of the current environment variable with the name. */
                if (_strncmp(environ[i], name, namelen) == 0 && environ[i][namelen] == '=')
                {
                        /* Return a pointer to the value of the environment variable. */
                        return (environ[i] + namelen + 1);
                }
        }

        /* If the variable is not found, return NULL. */
        return (NULL);
}
