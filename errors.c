#include "shell.h"

/**
 * _eputs - display input strings
 * @str: printing strings
 * Return: Null
 */
void _eputs(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_eputchar(str[t]);
		t++;
	}
}

/**
 * _eputchar - writes a character
 * @q: printed character
 *
 * Return: 1.
 */
int _eputchar(char q)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (q == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (q != BUF_FLUSH)
		buf[i++] = q;
	return (1);
}

/**
 * _putfd - writes a character
 * @q: printed character
 * @fd: file descriptor
 * Return: 1.
*/
int _putfd(char q, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (q == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (q != BUF_FLUSH)
		buf[t++] = q;
	return (1);
}

/**
 * _putsfd - displays string
 * @str: printing string
 * @fd: file descriptor
 * Return: no of characters
 */
int _putsfd(char *str, int fd)
{
	int t = 0;

	if (!str)
		return (0);
	while (*str)
	{
		t += _putfd(*str++, fd);
	}
	return (t);
}
