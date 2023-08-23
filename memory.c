#include "shell.h"

/**
 * bfree - it’s a pointer
 * @ptr: address of free pointer
 *
 * Return: 1 true, false 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
