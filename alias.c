#include "main.h"

/**
 * _alias - Builtin command that prints all aliases
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @fro: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _alias(char **args, char __attribute__((__unused__)) **fro)
{
	aliases_t *temp = aliases;
	int i, r = 0;
	char *v;

	if (!args[0])
	{
		while (temp)
		{
			_alias_p(temp);
			temp = temp->next;
		}
		return (r);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		v = str_chr(args[i], '=');
		if (!v)
		{
			while (temp)
			{
				if (str_cmp(args[i], temp->name) == 0)
				{
					_alias_p(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				r = _c_error_(args + i, 1);
		}
		else
			_aliaser(args[i], v);
	}
	return (r);
}

/**
 * _aliaser - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @_var: Name of the alias.
 * @v: Value of the alias. First character is a '='.
 */
void _aliaser(char *_var, char *v)
{
	aliases_t *temp = aliases;
	int len, j, k;
	char *new_v;

	*v = '\0';
	v++;
	len = str_len(v) - str_spn(v, "'\"");
	new_v = malloc(sizeof(char) * (len + 1));
	if (!new_v)
		return;
	for (j = 0, k = 0; v[j]; j++)
	{
		if (v[j] != '\'' && v[j] != '"')
			new_v[k++] = v[j];
	}
	new_v[k] = '\0';
	while (temp)
	{
		if (str_cmp(_var, temp->name) == 0)
		{
			free(temp->v);
			temp->v = new_v;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		a_alias_e(&aliases, _var, new_v);
}

/**
 * _alias_p - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void _alias_p(aliases_t *alias)
{
	char *alias_str;
	int len = str_len(alias->name) + str_len(alias->v) + 4;

	alias_str = malloc(sizeof(char) * (len + 1));
	if (!alias_str)
		return;
	str_cpy(alias_str, alias->name);
	str_cat(alias_str, "='");
	str_cat(alias_str, alias->v);
	str_cat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, len);
	free(alias_str);
}
/**
 * _alias_r - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **_alias_r(char **args)
{
	aliases_t *temp;
	int i;
	char *new_v;

	if (str_cmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (str_cmp(args[i], temp->name) == 0)
			{
				new_v = malloc(sizeof(char) * (str_len(temp->v) + 1));
				if (!new_v)
				{
					f_args(args, args);
					return (NULL);
				}
				str_cpy(new_v, temp->v);
				free(args[i]);
				args[i] = new_v;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
