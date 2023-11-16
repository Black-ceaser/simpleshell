#include "shell.h"

/**
 * _strlen - length of string
 * @s: string to be checked
 * Return: length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s++)
		a++;
	return (a);
}
/**
 * _strcmp - comapres two strings
 * @s1: first strand
 * @s2: second strand
 * Return: negative or positve
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
 * starts_with - checks the beginnig of a haystack
 * @haystack: string to be checked
 * @needle: substing to be checked
 * Return: pointer
 */
char *starts_with(const char *haystack, const char *needle)
{
	while  (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - adds two strings
 * @dest: destination buffer
 * @src: source
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *rett = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rett);
}
