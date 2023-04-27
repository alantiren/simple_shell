#include "shell.h"

#define UNUSED(x) (void)(x)


/**
 * _path - Function to fin the $PATH in the program environment.
 * @arr: (Array of poiters), arguments of the program tu execute.
 * @s: Size of the (Array of pointers - aop).
 * @_enviro: Current environment where the program is executed.
 * @wstatus: Return status of the las program executed.
 * Return - void.
 */

void _path(char **arr, int s, char **_enviro, int *wstatus)
{
	char **throgh = NULL, temp[3000];
	char m[6] = "PATH=";
	int i = 0, ienviro = 0, strc = 0, lenth = 0, r = 0;

	UNUSED(r);

	while (*_enviro)
	{
		if (_enviro[ienviro])
		{
			str_cpy(temp, _enviro[ienviro], 1);
			ienviro++;
		}

		while (temp[i] == m[i])
		{
			i++;
		}

		if (i == 5)
		{
			lenth = str_len(temp);
			throgh = sp_organ(temp, "PATH=:\n", lenth, &strc);
			r = _fixer(arr, throgh, s, strc, wstatus);
			*wstatus = r;
			liberay_p(throgh, strc);
			return;
		}
	}
}
