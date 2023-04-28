#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define UNUSED(x) (void)(x)
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_ARGUMENT_LENGTH 50

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
/**
 * shell_loop - loop that repeatedly prompts the user.
 * Description: contains a loop
 * Return: (EXIT_SUCCESS) on success, (EXIT_FAILURE) on success.
 */
int shell_loop(void)
{
int should_run = 1;
char line[MAX_COMMAND_LENGTH];
pid_t pid;
char *argv[] = { "/bin/ls", "-l", NULL };
char *env_point[] = { "PATH=/bin", "TERM=linux", NULL };
execve("/bin/ls", argv, env_point);
while (should_run)
printf("ourshell$ ");
fflush(stdout);
if (fgets(line, MAX_COMMAND_LENGTH, stdin) == NULL || feof(stdin))
{
printf("\n");
return (EXIT_SUCCESS);
}
else
{
perror("fgets");
return (EXIT_FAILURE);
}
line[_strspn(line, "\n")] = '\0';
pid = fork();
if (pid < 0)
{
perror("fork");
return (EXIT_FAILURE);
}
else if (pid == 0)
if (execve(line, argv, env_point) == -1)
if (errno == ENOENT)
printf("%s: command not found\n", line);
if (errno == EACCES)
printf("%s: permission denied\n", line);
else
perror("execve");
exit(EXIT_FAILURE);
{
wait(NULL);
}
return (EXIT_SUCCESS);
}
