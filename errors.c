#include "shell.h"

/**
 *errors - prints an input string to the console
 * @str: the string to be printed
 *
 * Return: void (nothing)
 */
void errors(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_errorcha(str[i]);
		i++;
	}
}

/**
 * _errorcha - writes the character c to stderr
 * @c: The character to be printed
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno.
 */
int _errorcha(char c)
{
	static int i;
	static char buf[BUFSIZE];

	if (c == TOK_BUFSIZE || i >= BUFSIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != TOK_BUFSIZE)
		buf[i++] = c;
	return (1);
}

/**
 * _writefd - writes a character to a specified file descriptor (fd)
 * @c: The character to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno.
 */
int _writefd(char c, int fd)
{
	static int i;
	static char buf[BUFSIZE];

	if (c == TOK_BUFSIZE || i >= BUFSIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != TOK_BUFSIZE)
		buf[i++] = c;
	return (1);
}

/**
 *_writesfd - writes a string to a file descriptor
 * @str: the string to be printed
 * @fd: The file descriptor to write to
 * Return: The number of characters written.
 * On error, returns -1 and sets errno.
 */
int _writesfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _writefd(*str++, fd);
	}
	return (i);
}
