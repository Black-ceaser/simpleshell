#include "shell.h"

/**
 * _strncpy - copies string
 * @dest: destination where string is copied to
 * @src: source string
 * @n: num of character to be copied
 * Return: joint string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;
	int j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - adds two strings
 * @dest: first string
 * @src: second string
 * @n: maximall amount of bytes used
 * Return: string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b = 0;
	char *s = dest;

	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 * _strchr - identifies character in a string
 * @s: string to be checked
 * @c: character to be searched for
 * Return: s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
