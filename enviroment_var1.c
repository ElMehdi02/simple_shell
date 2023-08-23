#include "main.h"
/**
 * _myunsetenv - remove an env variable
 * @info: struct
 * Return: Always 0
 */
int _myunsetenv(info_st *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * _unsetenv - Remove an env variable
 * @info: struct
 * @var: the string env variable property
 * Return: 1 on delete, 0 if not
 */
int _unsetenv(info_st *info, char *var)
{
	list_st *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - init a new env variable or modify an existing one
 * @info: struct
 * @var: the string env variable property
 * @value: the string env variable value
 * Return: Always 0
 */
int _setenv(info_st *info, char *var, char *value)
{
	char *buf = NULL;
	list_st *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
