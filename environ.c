-#include "shell.h"

/**
 * _getenv - get value of an environment variable
 * @name: the name of the variable
 *
 * Return: the value of the variable or NULL if not found
 */
char *_getenv(const char *name)
{
    int i, len;

    if (!name || !*name)
        return (NULL);

    len = _strlen(name);

    for (i = 0; environ[i]; ++i)
    {
        if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
            return (environ[i] + len + 1);
    }

    return (NULL);
}

/**
 * _setenv - set an environment variable
 * @name: the name of the variable
 * @value: the value of the variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value)
{
    int i, len;
    char *new_value;

    if (!name || !*name)
        return (-1);

    len = _strlen(name);

    for (i = 0; environ[i]; ++i)
    {
        if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
        {
            new_value = _realloc(environ[i], len + _strlen(value) + 2);

            if (!new_value)
                return (-1);

            new_value[len] = '=';
            _strcpy(new_value + len + 1, value);
            environ[i] = new_value;

            return (0);
        }
    }

    new_value = _malloc(len + _strlen(value) + 2);

    if (!new_value)
        return (-1);

    _strcpy(new_value, name);
    new_value[len] = '=';
    _strcpy(new_value + len + 1, value);
    environ[i] = new_value;
    environ[i + 1] = NULL;

    return (0);
}

/**
 * _unsetenv - remove an environment variable
 * @name: the name of the variable
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    int i, len;

    if (!name || !*name)
        return (-1);

    len = _strlen(name);

    for (i = 0; environ[i]; ++i)
    {
        if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
        {
            _free(environ[i]);

            while (environ[i + 1])
            {
                environ[i] = environ[i + 1];
                ++i;
            }

            environ[i] = NULL;

            return (0);
        }
    }

    return (0);
}
