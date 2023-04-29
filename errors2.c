#include "main.h"

/**
 * _error1env_ - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error1env_(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 45;
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
	str_cat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * _error_ - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error_(char **args)
{
	char *error;
	int len;

	len = str_len(name) + str_len(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	str_cpy(error, "alias: ");
	str_cat(error, args[0]);
	str_cat(error, " not found\n");

	return (error);
}

/**
 * _errorexit_ - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_errorexit_(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": exit: Illegal number: ");
	str_cat(error, args[0]);
	str_cat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * _errorcd_ - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_errorcd_(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		str_cat(error, ": cd: Illegal option ");
	else
		str_cat(error, ": cd: can't cd to ");
	str_cat(error, args[0]);
	str_cat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * _errorsyntax_ - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_errorsyntax_(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": Syntax error: \"");
	str_cat(error, args[0]);
	str_cat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
