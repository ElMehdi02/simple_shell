#include "shell.h"

/**
 * hsh - this is the main shell loop
 * @info: contains a parameter & the return info structucture
 * @av: argument vector
 *
 * Return: 0 if successful, 1 on failure
 */
int hsh(info_r *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds the built in command
 * @info: contains a parameter and structure
 * Return: -1 builtin absent,
 *	0 if execution successfully,
 *	1 if not successful but builtin found,
 *	2 signal present
 */
int find_builtin(info_r *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _isexit},
		{"env", _isenv},
		{"help", _ishelp},
		{"history", _ishistory},
		{"setenv", _issetenv},
		{"unsetenv", _isunsetenv},
		{"cd", _iscd},
		{"alias", _isalias},
		{NULL, NULL}
	};

	for (b = 0; builtintbl[i].type; b++)
		if (_strcmp(info->argv[0], builtintbl[b].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[b].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - used to locate a command path
 * @info: two function parameter and structure
 * Return: void
 */
void find_cmd(info_r *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[i]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			x++;
	if (!y)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks execution
 * @info: two functions parameter and structure
 * Return: void
 */
void fork_cmd(info_r *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
