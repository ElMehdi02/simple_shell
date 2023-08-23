#include "shell.h"

/**
 * _erratoi - handles string conversion
 * @g: pointer to string that needs conversion
 *
 * Return: the int value of converted string, else -1
 */
int _erratoi(char *g)
{
	int t = 0;
	unsigned long int result = 0;

	if (*g == '+')
		g++;
	for (t = 0;  g[t] != '\0'; t++)
	{
		if (g[t] >= '0' && g[t] <= '9')
		{
			result *= 10;
			result += (g[t] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - displays error messages
 * @info: struct containing arguments
 * @estr: pointer to error message
 */
void print_error(info_r *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_f(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_f - prints a decimal
 * @input: input
 * @fd: file descriptor
 *
 * Return: int value of characters printed
 */
int print_f(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int t, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_abs_ / t)
		{
			__putchar('0' + current / t);
			count++;
		}
		current %= t;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * conv_number - function converter
 * @num: integer number to convert
 * @base: the conversion base
 * @flags: flags for conversion
 *
* Return: string
 */
char *conv_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long c = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		c = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - removes comments
 * @buf: string address
 * Return: 0;
 */
void remove_comments(char *buf)
{
	int t;

	for (t = 0; buf[i] != '\0'; t++)
		if (buf[t] == '#' && (!t || buf[t - 1] == ' '))
		{
			buf[t] = '\0';
			break;
		}
}
