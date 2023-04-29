#include "main.h"

/**
 * _opener - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @_fpath: Path to the supposed file.
 *
 * Return: 127.
 */

int _opener(char *_fpath)
{
	char *error, *_hist_str;
	int len;

	_hist_str = _itoa_(hist);
	if (!_hist_str)
		return (127);

	len = str_len(name) + str_len(_hist_str) + str_len(_fpath) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(_hist_str);
		return (127);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, _hist_str);
	str_cat(error, ": Can't open ");
	str_cat(error, _fpath);
	str_cat(error, "\n");

	free(_hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proces_f_comm - Takes a file and attempts to run the commands stored
 * within.
 * @_fpath: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proces_f_comm(char *_fpath, int *exe_ret)
{
	ssize_t file, b_read_, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **fronter;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(_fpath, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = _opener(_fpath);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read_ = read(file, buffer, 119);
		if (b_read_ == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read_] = '\0';
		line_size += b_read_;
		line = _r_alloc_(line, old_size, line_size);
		str_cat(line, buffer);
		old_size = line_size;
	} while (b_read_);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	var_replacer(&line, exe_ret);
	handle_l(&line, line_size);
	args = str_tok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (ch_args(args) != 0)
	{
		*exe_ret = 2;
		f_args(args, args);
		return (*exe_ret);
	}
	fronter = args;

	for (i = 0; args[i]; i++)
	{
		if (str_ncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = c_args(args, fronter, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = c_args(args, fronter, exe_ret);

	free(fronter);
	return (ret);
}
