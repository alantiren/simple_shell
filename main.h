#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Environemnt */
extern char **environment;
extern char **environ;
/* Program Name */
char *name;

/* History Counter */
int hist;

/**
 * struct lists_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct lists_s
{
	char *dir;
	struct lists_s *next;
} lists_t;

/**
 * struct builtins_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtins_s
{
	char *name;
	int (*f)(char **argv, char **fronter);
} builtins_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct aliases_s
{
	char *name;
	char *v;
	struct aliases_s *next;
} aliases_t;

/* aliases linked_list */
aliases_t *aliases;
int _alias(char **args, char __attribute__((__unused__)) **fro);
void _aliaser(char *_var, char *v);
void _alias_p(aliases_t *alias);
/* Main Helpers */
ssize_t _g_line_(char **lineptr, size_t *n, FILE *stream);
void *_r_alloc_(void *ptr, unsigned int old_size, unsigned int new_size);
char **str_tok(char *line, char *delim);
char *g_loca(char *command);
lists_t *gpath_dir(char *path);
int _exec_(char **args, char **fronter);
void f_list(lists_t *head);
char *_itoa_(int num);
void a_line_p(char **lineptr, size_t *n, char *buffer, size_t b);
aliases_t *a_alias_e(aliases_t **head, char *name, char *v);
void f_alias_l(aliases_t *head);
lists_t *a_node_e(lists_t **head, char *dir);
char *fpath_dir(char *path);
/* Input Helpers */
void handle_l(char **line, ssize_t read);
void var_replacer(char **args, int *exe_ret);
char *g_args(char *line, int *exe_ret);
int c_args(char **args, char **fronter, int *exe_ret);
int r_args(char **args, char **fronter, int *exe_ret);
int h_args(int *exe_ret);
int ch_args(char **args);
void f_args(char **args, char **fronter);
char **r_alias(char **args);
ssize_t _gnew_len_(char *line);
void _log_ops_(char *line, ssize_t *new_len);
char *_gpid(void);
char *genv_v(char *beginning, int len);
void v_replacement(char **args, int *exe_ret);
/* String functions */
int str_len(const char *s);
char *str_cat(char *dest, const char *src);
char *str_ncat(char *dest, const char *src, size_t n);
char *str_cpy(char *dest, const char *src);
char *str_chr(char *s, char c);
int str_spn(char *s, char *accept);
int str_cmp(char *s1, char *s2);
int str_ncmp(const char *s1, const char *s2, size_t n);
int len_toke(char *str, char *delim);
int token_c(char *str, char *delim);
/* Builtin1 */
int (*_builtin(char *command))(char **args, char **fronter);
int _exiter(char **args, char **fronter);
int _env(char **args, char __attribute__((__unused__)) **fro);
int _setenv(char **args, char __attribute__((__unused__)) **fro);
int _unset_env(char **args, char __attribute__((__unused__)) **fro);
int _cd_(char **args, char __attribute__((__unused__)) **fro);
int _alias(char **args, char __attribute__((__unused__)) **fro);
int _helper_(char **args, char __attribute__((__unused__)) **fro);
/* Builtin2 */
char **_cenv_(void);
void _fenv_(void);
char **_genv_(const char *var);

/* Error Handling */
int _c_error_(char **args, int err);
char *_error1env_(char **args);
char *_error_(char **args);
char *_errorexit_(char **args);
char *_errorcd_(char **args);
char *_errorsyntax_(char **args);
char *_error126_(char **args);
char *_error127_(char **args);

/* Linkedlist Helpers */
aliases_t *a_alias_e(aliases_t **head, char *name, char *v);
void f_alias_l(aliases_t *head);
lists_t *a_node_e(lists_t **head, char *dir);
void f_list(lists_t *head);

void shellie_help_all(void);
void shellie_help_alias(void);
void shellie_help_cd(void);
void shellie_help_exit(void);
void shellie_help_help(void);
void shellie_help_env(void);
void shellie_help_set_env(void);
void shellie_help_unset_env(void);
void shellie_help_hist(void);
void _shand_(int sig);

char **_alias_r(char **args);

int proces_f_comm(char *_fpath, int *exe_ret);
int _opener(char *file_path);
int _n_len_(int num);
#endif /* MAIN_H */
