#include "shell.h"

/**
 * _isenv - printing the working environment
 * @info: Structure contains potential arguments
 * Return: Always 0
 */
int _isenv(info_r *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - getting environment value
 * @info: structure containing arguments
 * @name: string containing name
 *
 * Return: value
 */
char *_getenv(info_r *info, const char *name)
{
	list_t *node = info->env;
	char *v;

	while (node)
	{
		v = starts_with(node->str, name);
		if (v && *v)
			return (v);
		node = node->next;
	}
	return (NULL);
}

/**
 * _issetenv - Initializing new variable
 * @info: Structure contains arguments
 *  Return: 0
 */
int _issetenv(info_r *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _isunsetenv - environment variable removal
 * @info: Structure contains potential arguments
 * Return: 0
 */
int _isunsetenv(info_r *info)
{
	int t;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (t = 1; t <= info->argc; t++)
		_unsetenv(info, info->argv[t]);

	return (0);
}

/**
 * populate_env_list - fills environments linked list
 * @info: Structure contains arguments
 * Return: Always 0
 */
int populate_env_list(info_r *info)
{
	list_t *node = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&node, environ[t], 0);
	info->env = node;
	return (0);
}
