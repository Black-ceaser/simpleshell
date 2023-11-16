#include "shell.h"

/**
 * bfree - frees memory
 * @ptr: pointer to free
 * Return: 1 or 0
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
