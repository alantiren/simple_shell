#include "shell.h"

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
