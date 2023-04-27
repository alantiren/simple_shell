#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define UNUSED(x) (void)(x)
#define MAX_LINE_LENGTH 100

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
{
char line[MAX_LINE_LENGTH];
int should_run = 1;
pid_t pid;
while (should_run)
{
printf("simple_shell$ ");
fflush(stdout);
if
(fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
(feof(stdin))
{
printf("\n");
return (EXIT_SUCCESS);
}
else
perror("fgets");
return (EXIT_FAILURE);
line[strcspn(line, "\n")] = '\0';
pid = fork();
if (pid < 0)
perror("fork");
return (EXIT_FAILURE);
else if
(pid == 0)
if
(execve(line, argv, env_point) == -1)
(errno == ENOENT)
printf("%s: command not found\n", line);
else if (errno == EACCES)
printf("%s: permission denied\n", line);
else
perror("execve");
exit(EXIT_FAILURE);
else
wait(NULL);
}
return (EXIT_SUCCESS);
}
