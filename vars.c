#include "shell.h"

/**
 * is_chain - checks for a delimeter
 * @info: parameter
 * @buf: character buffer
 * @p: current buffer position
 *
 * Return: if a delimeter 1, else 0
 */
int is_chain(info_r *info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';') /* found end of this command */
	{
		buf[y] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = y;
	return (1);
}

/**
 * check_chain - checks for chaining
 * @len: buffer length
 * @p: address of current position in buf
 * @buf: character buffer
 *@info: parameter structucture
 * @i: buffer starting position
 *
 * Return: Void
 */
void check_chain(info_r *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t y = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}

	*p = y;
}

/**
 * replace_alias - replaces alias
 * @info: parameter structure
 * Return: 1 if successful, 0 if not
 */
int replace_alias(info_r *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replacing var tokenizer
 * @info: parameter structure
 * Return: 1 if successful, 0 if not
 */
int replace_vars(info_r *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replacing strings
 * @new: new string
 * @old: old string
 * Return: 1 if successful, 0 if not
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
