#include "main.h"

/*
 * char *get_loacat(char *cmd)
{
	char *path, *path_cpy, *path_token, *file_path;
	int cmd_length, dir_length;
	struct stat buff;
	info_st *info;

	path = get_path(info, _getenv(info, "PATH"), info->argv[0]);
	if (path)
	{
		path_cpy = _strdup(path);
		cmd_length = _strlen(cmd);
		path_token = strtok(path_cpy, ":");
		while (path_token != NULL)
		{
			dir_length = _strlen(path_token);
			file_path = malloc(cmd_length + dir_length + 2);

			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);
			_strcat(file_path, "\0");
			if (stat(file_path, &buff) == 0)
			{
				free(path_cpy);

				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_cpy);
		if (stat(cmd, &buff) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}
	return (NULL);
}
*/

/**
 * get_location - finds a command in path
 * @info: struct
 * Return: Always 0
 */
void get_location(info_st *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], "\t\n"))
			k++;
	if (!k)
		return;

	path = get_path(info, _getenv(info, "PATH"), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
