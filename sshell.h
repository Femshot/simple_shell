#ifndef S_SHELL_H
#define S_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

typedef struct builtins
{
	char *command;
	void (*ptr)(char **argvs);
} builtins_f;

int count_tokens(char *str);
char **create_token_array(char *str, int count);
void run_exe(char **av, char *path);
char *_strdup(char *str);
char *make_copy(char *str);
char *check_command(char *cmd, char **paths);
char *make_full_path(char *a, char *b, int c, int d);
int find_var(const char *name, int len);
char *_getenv(const char *name);
extern char **environ;
char **path_list(char *str, int count);
int count_path_tokens(char *str);
void exit_shell(char **arr);
int checking_built(char **arr);
void print_env(char **arr);
void free_safe(char *pointer);
int _putchar(char c);
void _puts(char *str);
int _strlen(const char *s);
void print_newprompt(char **arr);
void free_safe_2(char **pointer);
int print_error(char *pg, char *cmd, char **av);
void _puts2(char *str);
void start_prompt(char **s);
void end_prompt(char *p, int q);
int _atoi(char *s);
void print_number(int n);

#endif
