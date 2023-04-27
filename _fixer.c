#include "shell.h"
#define UNUSED(x) (void)(x)
/**
 * _fixer - function to find and execute the requested program.
 * @argu: Arrays of pointers where find the program arguments to execute.
 * @throgh: Path where the program to execute is.
 * @s0: Size of array (arguments).
 * @s1: Size of array (path).
 * @wstat: Return status of the las program executed.
 * Return: (0) Succes, the path was found and the program executed.
 */

int _fixer(char **argu, char **throgh, int s0, int s1, int *wstat)
{
	char *pfile = NULL, _cwd[1024];
	int r = 0, i = 0;

	UNUSED(pfile);
	UNUSED(r);
	getcwd(_cwd, sizeof(_cwd));
	while (throgh && throgh[i] && argu && s0 != 0 && s1 != 0)
	{
		if ((chdir(throgh[i])) < 0)
			return (-1);

		if ((access(argu[0], F_OK)) == 0)
		{
			pfile = str_cat(argu[0], throgh[i]);
			if (pfile)
			{
				if ((chdir(_cwd)) < 0)
					return (-1);
				r = _exetor(argu, pfile, s0);
				*wstat = r;

				if (r < 0)
				{
					free(pfile);
					return (*wstat);
				}
				else
				{
					free(pfile);
					return (*wstat);
				}
			}
		}
		i++;
	}
	if ((chdir(_cwd)) < 0)
		return (-1);
	free(pfile);
	printf("ourshell: %d: %s: not found\n", errno, argu[0]);
	return (-1);
}
