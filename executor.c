#include "shell.h"

/**
 * execute_command - Executes a command with given arguments
 * @args: Array of arguments to execute
 * @env: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char **args, char **env)
{
    int status;
    pid_t pid;
    char *command = args[0];
    char *path = NULL;

    if (is_builtin(command))
        return (execute_builtin(args, env));

    path = find_path(command, env);

    if (!path)
    {
        print_error("not found", command);
        return (0);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (0);
    }
    if (pid == 0)
    {
        if (execve(path, args, env) == -1)
        {
            perror("execve");
            free(path);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
        free(path);
    }

    return (1);
}

/**
 * is_builtin - Checks if a command is a built-in
 * @command: Command to check
 *
 * Return: 1 if command is a built-in, 0 otherwise
 */
int is_builtin(char *command)
{
    return (!strcmp(command, "exit") ||
            !strcmp(command, "env") ||
            !strcmp(command, "setenv") ||
            !strcmp(command, "unsetenv") ||
            !strcmp(command, "cd") ||
            !strcmp(command, "alias"));
}

/**
 * execute_builtin - Executes a built-in command
 * @args: Array of arguments to execute
 * @env: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int execute_builtin(char **args, char **env)
{
    int status = 1;

    if (!strcmp(args[0], "exit"))
        exit_shell(args, env);
    else if (!strcmp(args[0], "env"))
        print_env(env);
    else if (!strcmp(args[0], "setenv"))
        status = builtin_setenv(args, env);
    else if (!strcmp(args[0], "unsetenv"))
        status = builtin_unsetenv(args, env);
    else if (!strcmp(args[0], "cd"))
        status = builtin_cd(args, env);
    else if (!strcmp(args[0], "alias"))
        status = builtin_alias(args);

    return (status);
}

/**
 * find_path - Finds the path to a command
 * @command: Command to find
 * @env: Environment variables
 *
 * Return: Path to command on success, NULL on failure
 */
char *find_path(char *command, char **env)
{
    char *path = _getenv("PATH", env);
    char *dir, *tmp, *dup_path;
    struct stat st;

    dup_path = strdup(path);
    dir = strtok(dup_path, ":");
    while (dir)
    {
        tmp = _strcat(dir, "/");
        tmp = _strcat(tmp, command);
        if (stat(tmp, &st) == 0)
        {
            free(dup_path);
            return (tmp);
        }
        free(tmp);
        dir = strtok(NULL, ":");
    }

    free(dup_path);
    return (NULL);
}
