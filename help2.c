#include "main.h"

/**
 * f_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @fronter: A double pointer to the beginning of args.
 */
void f_args(char **args, char **fronter)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(fronter);
}

/**
 * _gpid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *_gpid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * genv_v - Gets the value corresponding to an environmental variable.
 * @begin: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *genv_v(char *begin, int len)
{
	char **var_addr;
	char *replace_ment = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	str_ncat(var, begin, len);

	var_addr = _genv_(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replace_ment = malloc(str_len(temp) + 1);
		if (replace_ment)
			str_cpy(replace_ment, temp);
	}

	return (replace_ment);
}

/**
 * var_replacer - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void var_replacer(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replace_ment = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replace_ment = _gpid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replace_ment = _itoa_(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replace_ment = genv_v(&old_line[j + 1], len);
			}
			new_line = malloc(j + str_len(replace_ment)
					  + str_len(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			str_ncat(new_line, old_line, j);
			if (replace_ment)
			{
				str_cat(new_line, replace_ment);
				free(replace_ment);
				replace_ment = NULL;
			}
			str_cat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
