#include "shell.h"
/**
 * _strcpy - copies string
 * @dest: destination
 * @src: source
 * Return: destination of pointer
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _puts - print input str
 * @str: string that is to be printed
 * Return: void
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUFF_S];

	if (c == BUFF_FLUSH || a >= WRITE_BUFF_S)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUFF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _strdup - dupicates string
 * @str: sting duplicate
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *rett;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	rett = malloc(sizeof(char) * (len + 1));
	if (!rett)
		return (NULL);
	for (len++; len--;)
		rett[len] = *--str;
	return (rett);
}
