#include "main.h"

/**
 * _shand_ - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void _shand_(int sig)
{
	char *new_prompt = "\n#cisfun$ ";

	(void)sig;
	signal(SIGINT, _shand_);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
<<<<<<< HEAD
 * _exec_ - Executes a command in a child process.
 * @args: An array of arguments.
 * @fronter: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int _exec_(char **args, char **fronter)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = g_loca(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (_c_error_(args, 126));
		else
			ret = (_c_error_(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (_c_error_(args, 126));
			_fenv_();
			f_args(args, fronter);
			f_alias_l(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "#$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, _shand_);

	*exe_ret = 0;
	environ = _cenv_();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proces_f_comm(argv[1], exe_ret);
		_fenv_();
		f_alias_l(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = h_args(exe_ret);
		_fenv_();
		f_alias_l(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = h_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			_fenv_();
			f_alias_l(aliases);
			exit(*exe_ret);
		}
	}

	_fenv_();
	f_alias_l(aliases);
	return (*exe_ret);
=======
 * shell_loop - loop that repeatedly prompts the user.
 * Description: contains a loop
 * Return: (EXIT_SUCCESS) on success, (EXIT_FAILURE) on failure.
 */
int shell_loop(void)
{
int should_run = 1;
char line[MAX_COMMAND_LENGTH];
pid_t pid = fork();
char *args[] = { "/bin/ls", "-l", NULL };
char *env_point[] = { "PATH=/bin", "TERM=linux", NULL };
execve("/bin/ls", args, env_point);
while (should_run)
printf("ourshell$ ");
fflush(stdout);
if (fgets(line, MAX_COMMAND_LENGTH, stdin) == NULL || feof(stdin))
{
printf("\n");
return (EXIT_SUCCESS);
}
else
{
perror("fgets");
return (EXIT_FAILURE);
}
line[_strspn(line, "\n")] = '\0';
pid = fork();
if (pid < 0)
{
perror("fork");
return (EXIT_FAILURE);
}
else if (pid == 0)
args[0] = line;
args[1] = NULL;
if (execve(line, args, env_point) == -1)
if (errno == ENOENT)
printf("%s: command not found\n", line);
if (errno == EACCES)
printf("%s: permission denied\n", line);
else
perror("execve");
exit(EXIT_FAILURE);

wait(NULL);
return (EXIT_SUCCESS);
>>>>>>> 4bf6e3832441f55be486fd656a55c8ce33955f14
}
