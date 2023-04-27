#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/**
 * sp_organ - Function to create a dynamic array of pointers
 * where store every argument given by user trough getilne().
 * @word: The original string to be separed into tokens with strtok().
 * @del: The delimiter characters for strtok().
 * @len: Lenght of the entire (string).
 * @strc: Variable where store the amount of tokens found
 * (variable needed by malloc).
 * Return: Success (Array of pointers - aop), where all tokens will be saved.
 */

char **sp_organ(char *word, const char *del, int len, int *strc)
{
	char *temp, *token, **arr;
	int i = 0, stlen[120];

	temp  = malloc(sizeof(char) * (len + 1));
	if (temp)
	{
		temp = str_cpy(temp, word, len);
		token = strtok(temp, del);

		while (token != NULL)
		{
			stlen[i] = str_len(token);
			token = strtok(NULL, del);
			(*strc)++;
			i++;
		}
		free(temp);
	}
	else
		perror("Buffer0 not found. (Malloc)");
	arr = malloc(sizeof(*arr) * (*strc + 1));
	for (i = 0; i < (*strc); i++)
		arr[i] = malloc(sizeof(char) * (stlen[i] + 1));
	arr[(*strc)] = NULL;
	if (arr)
	{
		i = 0;
		temp = strtok(word, del);
		arr[i] = str_cpy(arr[i], temp, (stlen[0] + 1));
		temp = strtok(NULL, del);
		while (arr[i] && temp)
		{
			i++;
			arr[i] = str_cpy(arr[i], temp, (stlen[i] + 1));
			temp = strtok(NULL, del);
		}
		return (arr);
	}
	return (NULL);
}
