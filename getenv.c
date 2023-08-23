#include "shell.h"

/**
 * get_environ - returns array string
 * @info: struct containing var
 *
 * Return: 0
 */
char **get_environ(info_r *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removal of variables
 * @info: struuct containing arguments
 * @var: string environment var
 *
 * Return: 1 if deleted, 0 if not
 */
int _unsetenv(info_r *info, char *var)
{
	list_t *node = info->env;
	size_t v = 0;
	char *x;

	if (!node || !var)
		return (0);

	while (node)
	{
		x = starts_with(node->str, var);
		if (x && *x == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			v = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		v++;
	}
	return (info->env_changed);
}

/**
 * _setenv - creates a new environment variable
 * @info: Structure contains arguments
 * @var: string variable
 * @value: value for the string variable
 *
 * Return: 0 when variable is created, else 1
 */
int _setenv(info_r *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *x;

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
		if (x && *x == '=')
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
