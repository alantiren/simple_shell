#include "shell.h"

/**
 * read_input - reads input from stdin and stores it in a buffer
 *
 * Return: buffer containing user input
 */
char *read_input(void)
{
char *buffer = NULL;
size_t bufsize = 0;

if (getline(&buffer, &bufsize, stdin) == -1)
{
if (feof(stdin))
{
free(buffer);
exit(EXIT_SUCCESS);
}
else
{
perror("read_input");
exit(EXIT_FAILURE);
}
}
return buffer;
}

/**
 * strip_newline - strips the newline character from a string
 * @str: the string to strip
 *
 * Return: pointer to the stripped string
 */
char *strip_newline(char *str)
{
size_t len = str_len(str);
if (len > 0 && str[len - 1] == '\n')
str[len - 1] = '\0';
return str;
}
