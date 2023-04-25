#include "shell.h"

/**
 * str_cpy - return the copie of one string.
 * @after: Copy after function execution.
 * @src: Original string to bi copied.
 * @n: Number of characters in src. (UNUSED).
 * Return: The string copied (dest).
*/

char *str_cpy(char *after, char *src, int n)
{
	int i = 0;

	if (after && src && n != 0)
	{
		for (i = 0; src[i] != '\0'; i++)
		{
			after[i] = src[i];
		}

		after[i] = '\0';
		return (after);
	}
	return (NULL);
}
