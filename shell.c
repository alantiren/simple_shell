#include "shell.h"

/**
 * main - Entry point for the simple_shell program
 * @argc: The number of arguments passed to the program
 * @argv: An array of strings containing the arguments passed to the program
 * @envp: An array of strings containing the environment variables
 *
 * Return: Always returns 0
 */
int main(int argc, char **argv, char **envp)
{
    char *line = NULL, **args = NULL, *full_path = NULL, *path = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int status = 0, count = 0, i = 0, flag = 0, exec_flag = 0, line_num = 0;
    struct stat st;
    hist_t *hist = NULL, *head = NULL;
    alias_t *alias = NULL, *alias_head = NULL;

    (void)argc;

    signal(SIGINT, signal_handler);

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ ", 2);

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        line_num++;
        if (read > 1 && line[read - 2] == '\\')
        {
            line[read - 2] = '\0';
            if (line[0] != '\0')
                add_history(&hist, line, line_num);
            continue;
        }

        if (line[0] == '\n')
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "$ ", 2);
            continue;
        }
        if (line[0] == '#')
        {
            if (line[1] != '\n')
                continue;
        }
        add_history(&hist, line, line_num);
        args = tokenize(line, " \t\r\n\a", 0);
        if (args == NULL)
            continue;
        for (i = 0; args[i] != NULL; i++)
        {
            count++;
            if (_strcmp(args[i], "&&") == 0 || _strcmp(args[i], "||") == 0)
                flag = 1;
            if (_strcmp(args[i], ";") == 0)
            {
                exec_flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            status = shell_logic(args, envp, &alias_head, &hist);
            flag = 0;
            continue;
        }
        else if (exec_flag == 1)
        {
            status = exec_commands(args, envp, &alias_head, &hist);
            exec_flag = 0;
            continue;
        }
        full_path = find_path(args[0], envp);
        if (full_path != NULL)
            status = execute_command(full_path, args, envp);
        else if (stat(args[0], &st) == 0)
            status = execute_command(args[0], args, envp);
        else
        {
            path = get_path(envp);
            print_error(args, count, path, line_num);
            free(path);
            status = 127;
        }
        free(full_path);
        free(args);
        count = 0;
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);
    }
    free(line);
    free_history(&hist);
    free_alias(&alias_head);
    exit(status);
}
