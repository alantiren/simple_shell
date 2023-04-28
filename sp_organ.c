#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * sp_organ - Split a string into tokens based on a delimiter
 * @line: Pointer to the string to split
 * @delim: Pointer to the delimiter string
 * Return: Pointer to an array of tokens
 */
char **sp_organ(char *line, const char *delim)
{
    char **tokens = NULL;
    char *token;
    int i = 0;

    /* Allocate memory for the tokens array */
    tokens = malloc(sizeof(char *));
    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Get the first token */
    token = strtok(line, delim);

    /* Loop through the rest of the tokens */
    while (token != NULL)
    {
        /* Allocate memory for the new token */
        tokens[i] = malloc(strlen(token) + 1);
        if (tokens[i] == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        /* Copy the token into the tokens array */
        strcpy(tokens[i], token);

        /* Increment the token count */
        i++;

        /* Resize the tokens array */
        tokens = realloc(tokens, sizeof(char *) * (i + 1));
        if (tokens == NULL)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        /* Get the next token */
        token = strtok(NULL, delim);
    }

    /* Add a NULL terminator to the end of the tokens array */
    tokens[i] = NULL;

    return tokens;
}
