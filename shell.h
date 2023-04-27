#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

#define MAX_ARGS 64
#define MAX_PATHS 1024
#define MAX_PATH_LEN 1024
#define BUFSIZE 1024

/* Global variables */
extern char **environ;

/* Function prototypes */
void prompt(void);
char **parse_input(char *);
int execute_command(char **);
int launch_process(char **);
int handle_builtin(char **);
void handle_cd(char **);
void handle_setenv(char **);
void handle_unsetenv(char **);
void handle_alias(char **);
void handle_exit(char **);
void handle_env(void);
void handle_variable_expansion(char **);
void handle_comments(char *);
void free_memory(char **);

/* Prompt */
void print_prompt(void);

/* Signal handling */
void signal_handler(int sig);

/* Command execution */
int execute_command(char **args);

/* Built-in commands */
int shell_cd(char **args);
int shell_alias(char **args);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_exit(char **args);
int shell_env(char **envp);

/* Path management */
char **get_paths(char *envp[]);
char *search_path(char *command, char *paths[], int num_paths);

/* String manipulation */
char *strip(char *str);
char **split(char *str, const char *delim);
int _atoi(char *s);

/* getline implementation */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* Variables handling */
void handle_variables(char **args);
char **parse_cmd(char *cmd);
char *replace_vars(char *str);
char *handle_var(char *str);

/* Handle commands with arguments, separator, logical operators */
int handle_commands(char *input);

/* Set and unset environment variables */
int set_env(char *name, char *value);
int unset_env(char *name);

/* Handle errors */
void print_error(char *message, int exit_status);

#endif /* SHELL_H */
