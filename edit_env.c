#include "shell.h"

/**
 * _getenv - gets the environment variable
 * @key: key to get the value of
 * Return: value of the environment variable
 */

char *_getenv(char *key)
{
	unsigned int i = 0;
	char *path;
	char **env;
	int count = 0, j = 0;

	while (environ[count])
		count++;

	env = malloc(sizeof(char *) * (count + 1));

	for (j = 0; j < count; j++)
		env[j] = _strdup(environ[j]);

	env[count] = NULL;

	while (env[i])
	{
		path = strtok(env[i], "=");
		if (_strcmp(key, env[i]) == 0)
		{
			path = strtok(NULL, "\n");
			return (path);
		}
		i++;
	}
	return (NULL);
}

/**
 * len_env - gets the length of the environment
 * @env: environment
 * Return: length of the environment
 */

int len_env(char **env)
{
	int i = 0;

	while (env[i])
		i++;
	return (i);
}
