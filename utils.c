#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 50

void execute_command(char* command)
{
    pid_t pid;
    int status;
    char* argv[] = { command, NULL };
    pid = fork();
    if (pid == 0) {
        /* Child process */
        execve(command, argv, environ);
        /* If execve returns, an error has occurred */
        fprintf(stderr, "Command not found: %s\n", command);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        fprintf(stderr, "Error forking process\n");
    } else {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

char* read_command()
{
    char* command = (char*)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    printf("Enter command: ");
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        /* End of file (Ctrl-D) */
        exit(EXIT_SUCCESS);
    }
    /* Remove newline character from end of command */
    command[strcspn(command, "\n")] = '\0';
    return command;
}
