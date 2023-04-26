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

/*   Our functions. */

char **sp_organ(char *, const char *, int len, int *strc);
int _fixer(char **argu, char **throgh, int s0, int s1, int *);
int _taker(char **argu, int s, char **_enviro, int *wstatus);
int _exetor(char **arr, const char *throgh, int s);
void print_enviro(char **env_point);
void liberay_p(char **arr, int s);
void _path(char **arr, int s, char **_enviro, int *wstatus);

/*   Generic functions. */

char *str_cpy(char *after, char *src, int n);
int str_len(char *str);
int str_cmp(char *s1, char *s2);
char *str_cat(char *after, char *src);

#endif /* _HEADERS_H_ */
