#ifndef _HEADERS_H_
#define _HEADERS_H_

/*   Libraries. */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h>



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
int shell_loop(void);
bool is_valid_executable(const char *filename);

/*   Generic functions. */

char *str_cpy(char *after, char *src, int n);
int str_len(char *str);
int str_cmp(char *s1, char *s2);
char *str_cat(char *after, char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strncmp(const char *s1, const char *s2, size_t n);

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

#endif
