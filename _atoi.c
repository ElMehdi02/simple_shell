#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: address of structure
 *
 * Return: 1 if successful, 0 if not
 */
int interactive(info_r *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checking if character is a delimeter
 * @delim: string delimeter
 * @b: checking character
 * Return: if true 1, if false 0
 */
int is_delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 * _isalpha - checking alphabetic characters
 * @b: input char
 * Return: 1 if true, 0 if not
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - handles conversions
 * @y: conversion string
 * Return: 0 if false, if true 1
 */

int _atoi(char *y)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0; y[n] != '\0' && flag != 2; n++)
	{
		if (y[n] == '-')
			sign *= -1;

		if (y[n] >= '0' && y[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (y[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
