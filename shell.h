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

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

char **token(char *buffer);
void free_arg(char **argv);
void env(void);

/* errors.c */
void errors(char *format);
int _errorcha(char);
int _writefd(char c, int fd);
int _writesfd(char *str, int fd);

int _getline(unsigned int fd, char *buffer, size_t bytes);
int cd(char *path);
char *path(char *filename);

#endif
