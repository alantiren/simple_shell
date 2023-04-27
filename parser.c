#include "shell.h"

/**
 * parse_cmd - Parses a command string into an array of arguments.
 * @cmd: The command string to parse.
 *
 * Return: An array of arguments, or NULL on failure.
 */
char **parse_cmd(char *cmd)
{
    char **args = NULL;
    char *token = NULL, *delim = " \t\n", *saveptr = NULL;
    size_t i, num_args = 0;

    if (cmd == NULL)
        return (NULL);

    /* Allocate space for arguments */
    args = malloc(MAX_ARGS * sizeof(char *));
    if (args == NULL)
        return (NULL);

    /* Parse command string */
    for (i = 0, token = strtok_r(cmd, delim, &saveptr);
         token != NULL && i < MAX_ARGS;
         i++, token = strtok_r(NULL, delim, &saveptr))
    {
        /* Replace any variable references with their values */
        token = replace_vars(token);

        /* Add argument to array */
        args[i] = token;
        num_args++;
    }

    /* Handle empty command */
    if (num_args == 0)
    {
        free(args);
        return (NULL);
    }

    /* Add NULL terminator */
    args[i] = NULL;

    return (args);
}

/**
 * replace_vars - Replaces variable references in a string with their values.
 * @str: The string to replace variables in.
 *
 * Return: The string with variables replaced, or NULL on failure.
 */
char *replace_vars(char *str)
{
    char *new_str = NULL, *var_name = NULL, *var_value = NULL;
    size_t i, j = 0, var_len = 0;

    if (str == NULL)
        return (NULL);

    /* Allocate space for new string */
    new_str = malloc(MAX_STR_LEN);
    if (new_str == NULL)
        return (NULL);

    /* Copy original string to new string, replacing variables */
    for (i = 0; str[i] != '\0' && j < MAX_STR_LEN - 1; i++)
    {
        if (str[i] == '$' && str[i + 1] != '\0')
        {
            /* Find end of variable name */
            for (var_len = 0; str[i + var_len + 1] != '\0' &&
                     is_valid_var_char(str[i + var_len + 1]);
                 var_len++)
                ;

            /* Extract variable name */
            var_name = strndup(&str[i + 1], var_len);

            /* Replace variable with its value */
            var_value = get_var_value(var_name);
            if (var_value != NULL)
            {
                strncpy(&new_str[j], var_value, MAX_STR_LEN - j - 1);
                j += strlen(var_value);
            }

            /* Free variable name and value */
            free(var_name);
            free(var_value);

            /* Skip past variable in original string */
            i += var_len;
        }
        else
        {
            new_str[j] = str[i];
            j++;
        }
    }

    /* Add NULL terminator */
    new_str[j] = '\0';

    return (new_str);
}

/**
* is_valid_var_char - Determines if a character is a valid variable name character.
* @c: The character to check.
* Return: 1 if the character is valid, otherwise 0.
*/
int is_valid_var_char(char c)
{
if (isalnum(c) || c == '_')
return (1);
return (0);
}
/**
* handle_var - Handles variable replacement within a string.
* @str: The string to handle variable replacement in.
* Return: A pointer to the new string with variable replacements, or NULL on failure.
*/
char *handle_var(char *str)
{
char *new_str, *var, *value;
int i, j, k, len;

new_str = malloc(sizeof(char) * (strlen(str) + 1));
if (!new_str)
return (NULL);

for (i = 0, j = 0; str[i]; i++)
{
if (str[i] == '$' && is_valid_var_char(str[i + 1]))
{
var = malloc(sizeof(char) * (MAX_VAR_LEN + 1));
if (!var)
{
free(new_str);
return (NULL);
}
for (k = 0, i++; is_valid_var_char(str[i]); k++, i++)
     {
         if (k >= MAX_VAR_LEN)
         {
             free(var);
             free(new_str);
             return (NULL);
         }
         var[k] = str[i];
     }
     var[k] = '\0';

     value = getenv(var);
     free(var);

     if (value)
     {
         len = strlen(value);
         for (k = 0; k < len; k++, j++)
             new_str[j] = value[k];
     }
     else
         new_str[j++] = '$';

     i--;
 }
 else
     new_str[j++] = str[i];
}

new_str[j] = '\0';
return (new_str);
}
