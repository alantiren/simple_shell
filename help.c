#include "main.h"
int (*_builtin(char *command))(char **args, char **fronter);
/*
 * g_args - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 * Return: If an error occurs - NULL.
 * Otherwise - a pointer to the stored command.
 */
char *g_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "#cisfun$ ";

	if (line)
		free(line);
	read = _g_line_(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (g_args(line, exe_ret));
	}
	line[read - 1] = '\0';
	var_replacer(&line, exe_ret);
	handle_l(&line, read);
	return (line);
}
/**
 * c_args - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @fronter: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 * Return: The return value of the last executed command.
 */
int c_args(char **args, char **fronter, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (str_ncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = _alias_r(args);
			ret = r_args(args, fronter, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (str_ncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = _alias_r(args);
			ret = r_args(args, fronter, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = _alias_r(args);
	ret = r_args(args, fronter, exe_ret);
	return (ret);
}
/**
 * r_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @fronter: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 * Return: The return value of the last executed command.
 */
int r_args(char **args, char **fronter, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **fronter);

	builtin = _builtin(args[0]);
	if (builtin)
	{
		ret = builtin(args + 1, fronter);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = _exec_(args, fronter);
		ret = *exe_ret;
	}
	hist++;
	for (i = 0; args[i]; i++)
		free(args[i]);
	return (ret);
}
/**
 * h_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int h_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **fronter;

	line = g_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);
	args = str_tok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (ch_args(args) != 0)
	{
		*exe_ret = 2;
		f_args(args, args);
		return (*exe_ret);
	}
	fronter = args;

	for (index = 0; args[index]; index++)
	{
		if (str_ncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = c_args(args, fronter, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = c_args(args, fronter, exe_ret);
	free(fronter);
	return (ret);
}
/**
 * ch_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int ch_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (_c_error_(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (_c_error_(&args[i + 1], 2));
		}
	}
	return (0);
}
