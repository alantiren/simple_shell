-#include "shell.h"

/**
 * _getline - Read a line from standard input
 * @lineptr: Pointer to a buffer where the input will be stored
 * @n: Pointer to the size of the buffer
 *
 * Return: Number of characters read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n)
{
        static char buffer[READ_SIZE];
        static ssize_t pos;
        ssize_t i, j;

        if (lineptr == NULL || n == NULL)
                return (-1);

        if (pos == 0)
        {
                /* Read in a chunk of input */
                pos = read(STDIN_FILENO, buffer, READ_SIZE);
                if (pos <= 0)
                        return (pos);
        }

        /* Find the next newline character */
        for (i = 0; i < pos; i++)
        {
                if (buffer[i] == '\n')
                {
                        /* Replace the newline with a null terminator */
                        buffer[i] = '\0';

                        /* Copy the line into the output buffer */
                        if (*lineptr == NULL)
                                *lineptr = malloc(i + 1);
                        else if (i + 1 > *n)
                        {
                                *n = i + 1;
                                *lineptr = realloc(*lineptr, *n);
                        }

                        if (*lineptr == NULL)
                                return (-1);

                        memcpy(*lineptr, buffer, i + 1);

                        /* Shift the remaining input left in the buffer */
                        pos -= i + 1;
                        memmove(buffer, buffer + i + 1, pos);

                        return (i);
                }
        }

        /* No newline found, copy the whole buffer */
        if (*lineptr == NULL)
                *lineptr = malloc(pos);
        else if (pos > *n)
        {
                *n = pos;
                *lineptr = realloc(*lineptr, *n);
        }

        if (*lineptr == NULL)
                return (-1);

        memcpy(*lineptr, buffer, pos);
        j = pos;
        pos = 0;

        return (j);
}
