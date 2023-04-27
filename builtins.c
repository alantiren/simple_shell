#include "shell.h"

/**
 * cd_builtin - change directory built-in function
 * @args: array of arguments
 * Return: 1 on success, 0 on failure
 */
int cd_builtin(char **args)
{
    char *dir;

    if (args[1] == NULL)
    {
        dir = getenv("HOME");
        if (dir == NULL)
            perror("Error");
    }
    else if (_strcmp(args[1], "-") == 0)
    {
        dir = getenv("OLDPWD");
        if (dir == NULL)
            perror("Error");
        else
            printf("%s\n", dir);
    }
    else
        dir = args[1];

    if (chdir(dir) != 0)
    {
        perror("Error");
        return (0);
    }

    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", getcwd(NULL, 0), 1);
    return (1);
}

/**
 * env_builtin - print environment built-in function
 * @args: array of arguments
 * Return: Always 1 (success)
 */
int env_builtin(char **args)
{
    int i;
    extern char **environ;

    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);

    return (1);
}

/**
 * setenv_builtin - set environment variable built-in function
 * @args: array of arguments
 * Return: 1 on success, 0 on failure
 */
int setenv_builtin(char **args)
{
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return (0);
    }

    if (setenv(args[1], args[2], 1) != 0)
    {
        perror("Error");
        return (0);
    }

    return (1);
}

/**
 * unsetenv_builtin - unset environment variable built-in function
 * @args: array of arguments
 * Return: 1 on success, 0 on failure
 */
int unsetenv_builtin(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return (0);
    }

    if (unsetenv(args[1]) != 0)
    {
        perror("Error");
        return (0);
    }

    return (1);
}

/**
 * exit_builtin - exit built-in function
 * @args: array of arguments
 * Return: Always -1 (to exit the shell)
 */
int exit_builtin(char **args)
{
    int status = 0;

    if (args[1] != NULL)
        status = _atoi(args[1]);

    exit(status);
    return (-1);
}
#include "shell.h"

/**
 * builtin_alias - Handles the 'alias' builtin command
 * @args: An array of arguments passed to the command
 *
 * Return: 1 on success, 0 on failure
 */
int builtin_alias(char **args)
{
    int i = 0;
    char *name = NULL, *value = NULL;

    /* Print all aliases if no arguments are passed */
    if (args[1] == NULL)
    {
        while (environ[i] != NULL)
        {
            if (startswith(environ[i], "alias="))
                printf("%s\n", environ[i] + 6);
            i++;
        }
        return (1);
    }

    /* Parse the arguments and define new aliases */
    while (args[i] != NULL)
    {
        /* Print an error message if an invalid argument is passed */
        if (!is_alias_arg(args[i]))
        {
            fprintf(stderr, "alias: invalid argument '%s'\n", args[i]);
            return (0);
        }

        /* Parse the alias name and value */
        name = strtok(args[i], "=");
        value = strtok(NULL, "=");

        /* If value is NULL, print the alias with the given name */
        if (value == NULL)
        {
            char *alias = get_alias(name);
            if (alias == NULL)
                fprintf(stderr, "alias: %s not found\n", name);
            else
                printf("%s\n", alias);
        }
        else
        {
            /* Define a new alias with the given name and value */
            char *alias = create_alias(name, value);
            if (alias == NULL)
            {
                fprintf(stderr, "alias: error creating alias\n");
                return (0);
            }
        }

        i++;
    }

    return (1);
}

/**
 * is_alias_arg - Checks if an argument is valid for the 'alias' command
 * @arg: The argument to check
 *
 * Return: 1 if the argument is valid, 0 otherwise
 */
int is_alias_arg(char *arg)
{
    /* An argument is valid if it is in the form 'name=value' or 'name' */
    char *equal = strchr(arg, '=');
    if (equal == NULL)
        return (1);
    else if (equal == arg)
        return (0);
    else
        return (1);
}

/**
 * get_alias - Retrieves an alias with a given name
 * @name: The name of the alias to retrieve
 *
 * Return: A string containing the value of the alias, or NULL if the alias
 *         does not exist
 */
char *get_alias(char *name)
{
    int i = 0;
    char *alias = NULL;

    /* Search for the alias with the given name */
    while (environ[i] != NULL)
    {
        if (startswith(environ[i], "alias "))
        {
            char *alias_name = environ[i] + 6;
            if (strcmp(alias_name, name) == 0)
            {
                /* Found the alias, return its value */
                alias = environ[i] + 6 + strlen(name) + 1;
                break;
            }
        }
        i++;
    }

    return (alias);
}

/**
 * create_alias - Defines a new alias with a given name and value
 *
 * @name: The name of the alias to create
 * @value: The value of the alias to create
 *
 * Return: 1 on success, 0 on failure
 */
int create_alias(char *name, char *value)
{
    alias_t *new_alias, *cur_alias;

    if (!name || !*name)
        return (0);

    new_alias = malloc(sizeof(alias_t));
    if (!new_alias)
        return (0);

    new_alias->name = _strdup(name);
    if (!new_alias->name)
    {
        free(new_alias);
        return (0);
    }

    new_alias->value = _strdup(value);
    if (!new_alias->value)
    {
        free(new_alias->name);
        free(new_alias);
        return (0);
    }

    new_alias->next = NULL;

    if (!shell.alias)
        shell.alias = new_alias;
    else
    {
        cur_alias = shell.alias;
        while (cur_alias->next)
            cur_alias = cur_alias->next;
        cur_alias->next = new_alias;
    }

    return (1);
}
