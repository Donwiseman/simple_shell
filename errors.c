#include "shell.h"

/**
 * num_to_str - use recursion to form a string literal
 * @num: num to be read into a string
 * @str: buffer to write string into
 *
 * Return: returns a string representation of number
 */
unsigned int num_to_str(unsigned int num, char *str)
{
	unsigned int index = 0;

	if ((num / 10) > 0)
		index += num_to_str((num / 10), str);
	str[index] = (num % 10) + 48;
	return (index++);
}

/**
 * convert_str - converts a number to a string literal
 * @count: number to be converted
 *
 * Return: a string representation of number
 */
char *convert_str(unsigned int count)
{
	char *str;
	unsigned int len = 1, num = count;

	while (num > 9)
	{
		num /= 10;
		len++;
	}
	str = (char *) malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	num_to_str(count, str);
	str[len] = '\0';
	return (str);
}

/**
 * errors - prints error message to the console
 * @sh_name: name of the shell being run
 * @command: name of the command that error occurred in
 * @count: count of program executed in this shell session
 *
 * Return: void (nothing)
 */
void errors(char *sh_name, char *command, unsigned int count)
{
	char err[128], *count_str = convert_str(count);
	unsigned int index, n = 0;

	if (count_str == NULL)
		exit(EXIT_FAILURE);
	for (index = 0; sh_name[index] != '\0'; index++)
		err[n++] = sh_name[index];
	err[n++] = ':';
	err[n++] = ' ';
	for (index = 0; count_str[index] != '\0'; index++)
		err[n++] = count_str[index];
	err[n++] = ':';
	err[n++] = ' ';
	for (index = 0; command[index] != '\0'; index++)
		err[n++] = command[index];
	err[n++] = '\0';
	free(count_str);
	perror(err);
}
