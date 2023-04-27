#include "shell.h"

/**
 * file_input - reads and executes commands from a file
 * @filename: name of the file containing the commands
 * Return: void
 */
void file_input(char *filename)
{
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int line_number = 0;

        fp = fopen(filename, "r");
        if (fp == NULL)
        {
                perror("Error opening file");
                return;
        }

        while ((read = getline(&line, &len, fp)) != -1)
        {
                line_number++;
                if (line[0] == '\n' || line[0] == '#')
                        continue;
                if (line[read - 1] == '\n')
                        line[read - 1] = '\0';
                if (execute_line(line) == EXIT_FAILURE)
                {
                        fprintf(stderr, "%s: %d: %s: %s\n", argv[0], line_number, line, "not found");
                        break;
                }
        }

        fclose(fp);
        if (line)
                free(line);
}
