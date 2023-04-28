#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define UNUSED(x) (void)(x)


/**
 * main - Entry point.
 * Description: Program to interpret adn execute programs defined of the $PATH.
 * @argc: Number of Arguments.
 * @argv: Array of arguments.
 * @env_point: environment of the executed current program.
 * Return: (EXIT)
 */

int main(int argc, char **argv, char **env_point)
{
char *ln = NULL, **arr, *_exit = "exit";
size_t lenth = 0;
ssize_t rc;
int strc = 0, wstatus = 0;
signal(SIGINT, SIG_IGN);
UNUSED(argc);
UNUSED(argv);
write(1, "cisfun$ ", 9);
while ((rc = getline(&ln, &lenth, stdin)) != EOF)
{
if (ln && (str_cmp(ln, _exit)) != 0)
{
strc = 0;
arr = sp_organ(ln, " \t\r\n\f\v", rc, &strc);
if (arr[0] != NULL)
{
_taker(arr, strc, env_point, &wstatus);
liberay_p(arr, strc);
}
else
free(arr);
write(1, "\ncisfun$ ", 10);
}
else if ((str_cmp(ln, _exit)) == 0)
{
free(ln);
exit(wstatus);
}
else
{
perror("Error, unable to allocate buffer\n");
}
}
free(ln);
exit(EXIT_SUCCESS);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define UNUSED(x) (void)(x)

/**
 * main - Entry point.
 * Description: Program to interpret and execute programs defined in the current directory.
 * @argc: Number of Arguments.
 * @argv: Array of arguments.
 * @env_point: environment of the executed current program.
 * Return: (EXIT_SUCCESS) on success, (EXIT_FAILURE) on failure.
 */

int main(int argc, char **argv, char **env_point)
{
    char *ln = NULL, *cmd = NULL;
    size_t len = 0;
    ssize_t rc;
    signal(SIGINT, SIG_IGN);
    UNUSED(argc);
    UNUSED(argv);
    while (1)
    {
        printf("cisfun$ ");
        rc = getline(&ln, &len, stdin);
        if (rc == EOF)
        {
            free(ln);
            putchar('\n');
            exit(EXIT_SUCCESS);
        }
        ln[strcspn(ln, "\n")] = '\0'; /* Remove newline character */
        if (strcmp(ln, "exit") == 0)
        {
            free(ln);
            putchar('\n');
            exit(EXIT_SUCCESS);
        }
        cmd = strdup(ln);
        if (cmd == NULL)
        {
            perror("Error");
            free(ln);
            continue;
        }
        if (fork() == 0)
        {
            if (execve(cmd, NULL, env_point) == -1)
            {
                perror("Error");
                free(cmd);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
            free(cmd);
        }
    }
    free(ln);
    return (EXIT_SUCCESS);
}


