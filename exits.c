#include "shell.h"

/**
 **_strncopy - duplicates a string
*@src: initial string
 *@n: no of copied characters
 *@dest: string copy destination
 *Return: new string
 */
char *_strncopy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[b] = src[a];
		b++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncut - concatenates strings
 *@dest: string one
 *@src: string two
 *@d: no of maximum bytes used
 *Return: new string
 */
char *_strncut(char *dest, char *src, int d)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[a] != '\0' && j < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < d)
		dest[a] = '\0';
	return (s);
}

/**
 * _strchr - character locator
 * @e: searching char
 * @f: passed string
 * Return: s
 */
char *_strchr(char *e, char f)
{
	do {
		if (*e == f)
			return (e);
	} while (*e++ != '\0');

	return (NULL);
}
