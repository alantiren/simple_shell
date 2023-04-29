#include "main.h"

/**
 *_ n_len_ - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int _n_len_(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa_ - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa_(int num)
{
	char *buffer;
	int len = _n_len_(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * _c_error_ - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int _c_error_(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = _error1env_(args);
		break;
	case 1:
		error = _error_(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = _errorexit_(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = _errorsyntax_(args);
		else
			error = _errorcd_(args);
		break;
	case 126:
		error = _error126_(args);
		break;
	case 127:
		error = _error127_(args);
		break;
	}
	write(STDERR_FILENO, error, str_len(error));

	if (error)
		free(error);
	return (err);

}
