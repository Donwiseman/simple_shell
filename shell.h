#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/**
 * struct data - dat combining various important parameters
 * @av: argeument vector from the shell being run
 * @input: input data
 * @args: arguments gotten from the user
 * @status: status program exited
 * @counter: program counter
 * @_environ: environ variable
 * @pid: process identifier
 */
typedef struct data
{
	char *av;
	char *input
	int _status;
	int _counter;
	char **_environ;
	char *pid;
	char *sh_name; /* name of the shell */
        char *input_line; /* input line from the user */
        char **args; /* array of arguments */
        int interactive_mode; /* whether the shell is in interactive mode or not */
        int cmd_count; /* count of the number of commands executed */
} data_shell;

/* envrn1.c  */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* envrn1.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd.c */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_shell.c */
int cd_shell(data_shell *datash);

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;
char **token(char *buffer);
void free_arg(char **argv);
void errors(char *sh_name, char *command, unsigned int count);
char *path(char *filename);
int _strncmp(char *s1, char *s2, int n);

#endif
