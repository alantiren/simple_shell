#include "main.h"

/**
 * shellie_help_env - Displays information on the shellby builtin
 * command 'env'
 */
void shellie_help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * shellie_help_set_env - Displays information on the shellby builtin
 * command 'setenv'.
 */
void shellie_help_set_env(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * shellie_help_unset_env - Displays information on the shellby builtin
 * command 'unsetenv'.
 */
void shellie_help_unset_env(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}
