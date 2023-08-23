#include "main.h"
/**
 * _strlen - gets the length of a givin string
 * @s: string
 * Return: string length
 */
int _strlen(char *s)
{
	int l = 0;

	if (!s)
		return (0);

	while (*s++)
		l++;
	return (l);
}

/**
 * _strcat - concatenates 2 strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to dest buffer
 */
char *_strcat(char *dest, char *src)
{
	char *res = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (res);
}
/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string
 * Return: pointer the the dup string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *res;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--;)
		res[len] = *--str;
	return (res);
}

/**
 * starts_with - checkes if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of the next char of haystack or null
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
