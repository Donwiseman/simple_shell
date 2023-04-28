#include "shell.h"
#include <string.h>

/**
 * execute_command - executes a given program from the argument vector
 * @sh_name: name which the shell program was called
 * @argv: argument vector for the argument to be excuted
 * @count: the current count of the programs sthe shell has executed
 *
 * Return: 0 if no errors otherwise -1
 */
int execute_command(char *sh_name, char **argv, unsigned int count)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		errors(sh_name, argv[0], count);
		return (-1);
	}
	else if (pid == 0)
	{
		if ((execve(argv[0], argv, environ)) < 0)
		{
			errors(sh_name, argv[0], count);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (!WIFEXITED(status))
			return (-1);
	}
	return (0);
}

/**
 * special_case - handles cases when command is not a relative or absolute path
 * @sh_name: name the shell was called for error printing
 * @argv: argument vector
 * @count: pointer to the counter for programs executed by the shell
 *
 * Return: 0 if program should continue normally, 1 if loop should be restarted
 * and 2 if loop should be broken (i.e exit)
 */
int special_case(char *sh_name, char **argv, int count)
{
	char *name;

	if (_strncmp(argv[0], "exit", 5) == 0)
		return (2);
	/**
	 * else if ((_strncmp(argv[0], "env", 4) == 0)
	 * {env();
	 * return (1);}
	 * else if ((_strncmp(argv[0], "cd", 3) == 0)
	 * {cd(argv[1]);
	 * return (1);}
	 */
	name = path(argv[0]);
	if (name == NULL)
	{
		errors(sh_name, argv[0], count);
		return (1);
	}
	else
	{
		free(argv[0]);
		argv[0] = name;
	}
	return (0);
}

/**
 * main - runs the simple shell program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 if executes with no error, otherwise 1
 */
int main(int ac, char **av)
{
	char **argv, *sh_name = av[0], *buffer = (char *) malloc(BUFSIZE);
	unsigned int count = 0, feed, is_term = 1;
	size_t n = BUFSIZE;

	if (ac > 1 || buffer == NULL)
	{
		errors(sh_name, av[1], count);
		exit(EXIT_FAILURE);
	}
	if ((isatty(STDIN_FILENO)) == 0)
		is_term = 0;
	else
		write(STDOUT_FILENO, "$ ", 2);
	while ((getline(&buffer, &n, stdin)) != -1)
	{
		argv = token(buffer);
		if (argv == NULL)
			continue;
		if (argv[0][0] != '/' && argv[0][0] != '.')
		{
			feed = special_case(sh_name, argv, ++count);
			if (feed == 2)
			{
				free_arg(argv);
				break;
			}
			else if (feed == 1)
			{
				free_arg(argv);
				continue;
			}
			count--;
		}
		execute_command(sh_name, argv, ++count);
		free_arg(argv);
		if (is_term)
			write(STDOUT_FILENO, "$ ", 2);
	}
	free(buffer);
	return (0);
}
