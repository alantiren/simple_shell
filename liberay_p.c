#include <stdlib.h>

/**
 * liberay_p - Frees memory allocated by sp_organ function.
 * @arr: Double pointer to the array of strings to be freed.
 * @strc: Number of strings in the array.
 *
 * Return: void
 */
void liberay_p(char **arr, int strc)
{
    int i;

    if (arr == NULL)
        return;

    for (i = 0; i < strc; i++)
    {
        if (arr[i])
            free(arr[i]);
    }
    free(arr);
}
