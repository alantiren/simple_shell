#include "shell.h"

/**
 * tokenizer - Tokenizes a string.
 * @str: The string to tokenize.
 *
 * Return: An array of tokens.
 */
char **tokenizer(char *str)
{
    char *token;
    char **tokens = malloc(sizeof(char *) * TOKENS_BUFFER_SIZE);
    size_t i = 0;

    if (!tokens)
    {
        perror("Error");
        return (NULL);
    }

    token = strtok(str, TOKEN_DELIMITERS);

    while (token != NULL)
    {
        tokens[i] = token;
        i++;

        if (i >= TOKENS_BUFFER_SIZE)
        {
            tokens = _realloc(tokens, sizeof(char *) * TOKENS_BUFFER_SIZE,
                              sizeof(char *) * (TOKENS_BUFFER_SIZE + TOKENS_BUFFER_INCREMENT));

            if (!tokens)
            {
                perror("Error");
                return (NULL);
            }

            TOKENS_BUFFER_SIZE += TOKENS_BUFFER_INCREMENT;
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }

    tokens[i] = NULL;

    return (tokens);
}
