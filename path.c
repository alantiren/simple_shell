#include "main.h"

/**
 * g_loca - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *g_loca(char *command)
{
	char **path, *temp;
	lists_t *dirs, *head;
	struct stat st;

	path = _genv_("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = gpath_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(str_len(dirs->dir) + str_len(command) + 2);
		if (!temp)
			return (NULL);

		str_cpy(temp, dirs->dir);
		str_cat(temp, "/");
		str_cat(temp, command);

		if (stat(temp, &st) == 0)
		{
			f_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	f_list(head);

	return (NULL);
}

/**
 * fpath_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fpath_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_genv_("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += str_len(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				str_cat(path_copy, pwd);
				str_cat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				str_cat(path_copy, ":");
				str_cat(path_copy, pwd);
			}
			else
				str_cat(path_copy, ":");
		}
		else
		{
			str_ncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * gpath_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
lists_t *gpath_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	lists_t *head = NULL;

	path_copy = fpath_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = str_tok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (a_node_e(&head, dirs[index]) == NULL)
		{
			f_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
