#include "shell.h"
/**
 * *_memset - fills the memory with constant bytes of code
 * @s: pointer to memory area
 * @b: bytes to be filled
 * @n: amount of bytes to be filled
 * Return: (s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}
/**
 * ffree - frees strings
 * @pp: strings super
 */
void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * _realloc - reallocates memory
 * @ptr: pointer
 * @old_size: byte size of previous block
 * @new_size: byte of new block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pt;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pt = malloc(new_size);
	if (!pt)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pt[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pt);
}
