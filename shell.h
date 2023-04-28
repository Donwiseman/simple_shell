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

typedef struct data
{
        char **av;
        char *input;
        char **args;
        int status;
        int counter;
        char **_environ;
        char *pid;
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
