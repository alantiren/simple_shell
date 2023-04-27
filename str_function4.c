#include "shell.h"

/**
 * str_cat - Function to concatenate the value character by
 * character of src to dest.
 * Description: "/bin" "ls" = "/bin/ls" - "src/dest" <-- e. Expected output.
 * @after: Variable on representetion of a program.
 * @src: Variable on representatio of the program path.
 * Return: Success (s_concat), string concatenated.
 **/

char *str_cat(char *after, char *src)
{
	char *concat = NULL;
	int lenafter = 0, lensrc = 0, i_s = 0, iafter = 0;

	if (after && src)
	{
		lenafter = str_len(after);
		lensrc = str_len(src);
		concat = malloc(sizeof(char) * (lenafter + lensrc + 2));

		if (concat)
		{
			while (src[i_s])
			{
				concat[i_s] = src[i_s];
				i_s++;
			}

			concat[i_s++] = '/';

			while (after[iafter])
			{
				concat[i_s] = after[iafter];
				iafter++;
				i_s++;
			}

			concat[i_s] = '\0';
			return (concat);
		}
	}
	perror("_strcat - Unable to find dest and src.");
	return (NULL);
}
