#include "shell.h"

/**
 * get_prompt - Prints a prompt and waits for user input.
 * @line: A pointer to the buffer to store user input.
 * @hist: A pointer to the history struct.
 *
 * Return: The number of characters read on success, or -1 on failure.
 */
ssize_t get_prompt(char **line, history_t *hist)
{
    ssize_t n_read;
    size_t len = 0;
    char *prompt = "$ ";
    char *input;

    /* Check if input is from a file or stdin */
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, prompt, _strlen(prompt));

    /* Read input */
    n_read = getline(&input, &len, stdin);

    /* Handle errors */
    if (n_read == -1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "\n", 1);
        if (errno == ENOMEM)
            perror("Memory allocation error");
        else if (errno != EOF)
            perror("Read error");
        return (-1);
    }

    /* Add input to history */
    if (hist)
        add_history(hist, input);

    /* Remove newline character */
    input[n_read - 1] = '\0';

    /* Allocate memory for input buffer */
    *line = malloc(_strlen(input) + 1);
    if (!*line)
    {
        perror("Memory allocation error");
        return (-1);
    }

    /* Copy input to buffer */
    _strcpy(*line, input);
    free(input);

    return (n_read);
}
