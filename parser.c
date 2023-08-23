#include "shell.h"

/**
 * is_cmd - checking file execution
 * @info: structure info
 * @path: file path
 * Return: 1 true, 0 false
 */
int is_cmd(info_r *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - copies characters
 * @pathstr: string path
 * @start: beginning index
 * @stop: ending index
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (a = 0, i = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[i];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - cmd path finder
 * @info: structure info
 * @pathstr: string path
 * @cmd: found cmd
 * Return: full cmd path
 */
char *find_path(info_r *info, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
