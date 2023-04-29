#include "main.h"

/**
 * _error126_ - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error126_(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": ");
	str_cat(error, args[0]);
	str_cat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * _error127_ - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error127_(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": ");
	str_cat(error, args[0]);
	str_cat(error, ": not found\n");

	free(hist_str);
	return (error);
}
