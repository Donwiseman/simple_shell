#include "shell.h"

/**
 * cd_dot - changes to the parent directory
 *
 * Return: no return
 */
int cd_dot(char *pathname)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dir = pathname;
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd,);
		free(cp_pwd);
		return (1);
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return (1);
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");
		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/");
	}
	free(cp_pwd);
	return (0);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: 0 or 1
 */
int cd_to(char *pathname)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));
	dir = pathname;
	if (chdir(dir) == -1)
	{
		return (1);
	}
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd);
	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir);
	free(cp_pwd);
	free(cp_dir);
	chdir(dir);
	return (0);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
int cd_previous()
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;
	int stat = 0;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	p_oldpwd = _getenv("OLDPWD");
	if (p_oldpwd == NULL)
	{
		errno = ENOENT;
		stat = 1;
		cp_oldpwd = cp_pwd;
	}
	else
		cp_oldpwd = _strdup(p_oldpwd);
	set_env("OLDPWD", cp_pwd);
	if (chdir(cp_oldpwd) == -1)
	{
		stat = 1;
		set_env("PWD", cp_pwd);
	}
	else
		set_env("PWD", cp_oldpwd);
	p_pwd = _getenv("PWD");
	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);
	chdir(p_pwd);
	return (stat);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
int cd_to_home()
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);
	home = _getenv("HOME");
	if (home == NULL)
	{
		errno = ENOENT;
		set_env("OLDPWD", p_pwd);
		free(p_pwd);
		return (1);
	}
	if (chdir(home) == -1)
	{
		free(p_pwd);
		return (1);
	}
	set_env("OLDPWD", p_pwd);
	set_env("PWD", home);
	free(p_pwd);
	return (0);
}
