#include "main.h"
/**
 * _myenv - prints the current env
 * @info: structure
 * Return: Always 0
 */
int _myenv(info_st *info)
{
	print_liststr(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: structure
 * @name: enviroment variable name
 * Return: env value
 */
char *_getenv(info_st *info, const char *name)
{
	list_st *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_environ - returns the string array copy of our environ
 * @info: struct
 * Return: environ
 */
char **get_environ(info_st *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * populate_env_list - populate env linked list
 * @info: struct
 * Return: Always 0
 */
int populate_env_list(info_st *info)
{
	list_st *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * _mysetenv - init a new env variable or modify an existing one
 * @info: struct
 * Return: Always 0
 */
int _mysetenv(info_st *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
