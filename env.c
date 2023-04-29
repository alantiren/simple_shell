#include "main.h"

/**
 * _cenv_ - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_cenv_(void)
{
	char **new_env;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_env[index] = malloc(str_len(environ[index]) + 1);

		if (!new_env[index])
		{
			for (index--; index >= 0; index--)
				free(new_env[index]);
			free(new_env);
			return (NULL);
		}
		str_cpy(new_env[index], environ[index]);
	}
	new_env[index] = NULL;

	return (new_env);
}

/**
 * _fenv_ - Frees the the environment copy.
 */
void _fenv_(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _genv_ - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_genv_(const char *var)
{
	int index, len;

	len = str_len(var);
	for (index = 0; environ[index]; index++)
	{
		if (str_ncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
