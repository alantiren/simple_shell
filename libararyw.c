#include "shell.h"

/**
 * liberay_p - Function to free an array of pointers.
 * @arr: (Array of pointers) to be freed.
 * @s: Size of the array.
 * Return - void.
*/

void liberay_p(char **arr, int s)
{
	int i = 0;

	if (arr && s != 0)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}

		free(arr);
		return;
	}
	else
	{
		perror("Array or size not received | That pointers are already free.");
		return;
	}
}
