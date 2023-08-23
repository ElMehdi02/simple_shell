#include "shell.h"

/**
 * _strlen - returns string length
 * @s: string length to be checked
 * Return: returns string length as integer
 */
int _strlen(char *s)
{
	int c = 0;

	if (!s)
		return (0);

	while (*s++)
		c++;
	return (c);
}

/**
 * _strcmp - comparison of two strings.
 * @s1: string one
 * @s2: string two
 * Return: (0) if s1 == s2, (+)  if s1 > s2, (-) if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checking needle
 * @haystack: searching string
 * @needle: find substring
 * Return: the null or address
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates
 * @dest: buffer destination
 * @src: buffer source
 * Return: points to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
