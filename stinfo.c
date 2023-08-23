#include "main.h"
/**
 * clear_info - initializes info_t structure
 * @info: struct address
 * Return: Always 0
 */
void clear_info(info_st *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t structure
 * @av: argument vector
 * @info: struct address
 * Return: Always 0
 */
void set_info(info_st *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tok(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = 1;

		replace_alias(info);
		replace_vars(info);
	}
}
