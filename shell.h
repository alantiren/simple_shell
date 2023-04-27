#ifndef _HEADERS_H_
#define _HEADERS_H_

/*   Libraries. */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/*   Our functions. */

char **sp_organ(char *, const char *, int len, int *strc);
int _fixer(char **argu, char **throgh, int s0, int s1, int *);
int _taker(char **argu, int s, char **_enviro, int *wstatus);
int _exetor(char **arr, const char *throgh, int s);
void print_enviro(char **env_point);
void liberay_p(char **arr, int s);
void _path(char **arr, int s, char **_enviro, int *wstatus);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int execute(char **args, char **front);
/*   Generic functions. */

char *str_cpy(char *after, char *src, int n);
int str_len(char *str);
int str_cmp(char *s1, char *s2);
char *str_cat(char *after, char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strncmp(const char *s1, const char *s2, size_t n);

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_PIPE	4

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* Handle errors */
void print_error(char *message, int exit_status);

/* Set and unset environment variables */
int set_env(char *name, char *value);
int unset_env(char *name);

/* Handle commands with arguments, separator, logical operators */
int handle_commands(char *input);

/* Variables handling */
void handle_variables(char **args);
char **parse_cmd(char *cmd);
char *replace_vars(char *str);
char *handle_var(char *str);

/* getline implementation */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* String manipulation */
char *strip(char *str);
char **split(char *str, const char *delim);
int _atoi(char *s);

/* Prompt */
void print_prompt(void);

/* Signal handling */
void signal_handler(int sig);

/* Command execution */
int execute_command(char **args);

#endif
