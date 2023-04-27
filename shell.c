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

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

int main() {
  char command[MAX_COMMAND_LENGTH];
  while (1) {
    printf(PROMPT);
    fflush(stdout); // Make sure the prompt is displayed before reading input
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
      printf("\n"); // Print a newline if Ctrl+D was pressed
      break;
    }
    size_t command_length = strlen(command);
    if (command[command_length - 1] == '\n') {
      command[command_length - 1] = '\0'; // Remove the newline
    }
    pid_t child_pid = fork();
    if (child_pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
      char* args[] = {command, NULL};
      execve(command, args, environ);
      perror("execve"); // If execve returns, it failed
      exit(EXIT_FAILURE);
    } else {
      int status;
      if (waitpid(child_pid, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
    }
  }
  return 0;
}
