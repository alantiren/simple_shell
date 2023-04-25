#include "shell.h"

/**
 * _taker - Function to take a decision if the first agrument[0]
 * is a path e."/bin" or is a program to be found e."ls".
 * @argu: Pointers array with the values entered by
 * the user trough getline().
 * @s: Size of pointers array.
 * @_enviro: Have the environment from where is executed the program.
 * - env will be pased as an argument of path_finder()
 * @wstatus: Return status of the las program executed.
 * Return: (0) Success, take a expected decition.
  **/

int _taker(char **argu, int s, char **_enviro, int *wstatus)
{
	char *comd_enviro = "env";
	int i = 0;

	if (argu && _enviro && s != 0)
	{
		if ((**argu == '/') | (**argu == '.'))
		{
			i = _exetor(argu, argu[0], s);
			*wstatus = i;
			return (*wstatus);
		}
		else
		{
			if ((str_cmp(argu[0], comd_enviro)) == 0)
			{
				print_enviro(_enviro);
				return (0);
			}
			else
			{
				_path(argu, s, _enviro, wstatus);
				return (0);
			}
		}
	}
	perror("Unable to find arguments, size or envp arguments.");
	return (-1);
}
