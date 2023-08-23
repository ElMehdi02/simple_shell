#include "shell.h"

/**
 * **strtow - splitting a string into two
 * @str: string input
 * @d: delimetre
 * Return: points array of strings, if failure points Null value
 */

char **strtow(char *str, char *d)
{
	int x, y, z, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[i] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[a], d))
			a++;
		z = 0;
		while (!is_delim(str[x + z], d) && str[x + z])
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < z; n++)
			s[y][n] = str[x++];
		s[y][n] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - splitting a string into two
 * @str: inputting string
 * @d: delimeter
 * Return: pointing an array of strings, if failure points Null
 */
char **strtow2(char *str, char d)
{
	int x, y, z, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < numwords; j++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		z = 0;
		while (str[x + z] != d && str[x + z] && str[x + z] != d)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (n = 0; m < z; n++)
			s[y][n] = str[x++];
		s[j][n] = 0;
	}
	s[y] = NULL;
	return (s);
}
