#include "shell.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * Return: no return
 */
void set_env(char *name, char *value)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; environ[i]; i++)
	{
		var_env = _strdup(environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	environ = _reallocdp(environ, i, sizeof(char *) * (i + 2));
	environ[i] = copy_info(name, value);
	environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @args: argument vector
 *
 * Return: 1 on success.
 */
int _setenv(char **args)
{

	if (args[1] == NULL || args[2] == NULL)
	{
		errno = EINVAL;
		return (1);
	}

	set_env(datash->args[1], datash->args[2]);

	return (0);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @args: argument vectors
 *
 * Return: 0 on success.
 */
int _unsetenv(char **args)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (args[1] == NULL)
	{
		errno = EINVAL;
		return (1);
	}
	k = -1;
	for (i = 0; environ[i]; i++)
	{
		var_env = _strdup(environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		errno = EINVAL;
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	environ = realloc_environ;
	return (0);
}
