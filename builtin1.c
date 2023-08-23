#include "shell.h"

/**
 * _ishistory - displays history
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int _ishistory(info_r *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - string to alias
 * @info: Structure parameter
 * @str: string alias
 *
 * Return:  0 on success, 1 if not
 */
int unset_alias(info_r *info, char *str)
{
	char *v, d;
	int ret;

	v = _strchr(str, '=');
	if (!v)
		return (1);
	d = *v;
	*v = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*v = d;
	return (ret);
}

/**
 * set_alias - string alias
 * @info: structure parameter
 * @str: string
 *
 * Return:  0 on success, 1 if wrong
 */
int set_alias(info_r *info, char *str)
{
	char *v;

	v = _strchr(str, '=');
	if (!v)
		return (1);
	if (!*++v)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - printing alias string
 * @node: alias node
 *
 * Return:  0 on success, 1 if not
 */
int print_alias(list_t *node)
{
	char *v = NULL, *a = NULL;

	if (node)
	{
		v = _strchr(node->str, '=');
		for (a = node->str; a <= v; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(v + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics alias
 * @info: Structure containing arguments
 *  Return: 0
 */
int _myalias(info_r *info)
{
	int k = 0;
	char *v = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		p = _strchr(info->argv[i], '=');
		if (v)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
