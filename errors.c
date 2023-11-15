#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - sends c to stderr
 * @c: character to print
 * Return: 1
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUFF_S];

	if (c == BUFF_FLUSH || a >= WRITE_BUFF_S)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUFF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - writes c to a given file descriptor
 * @c: character to be printed
 * @fd: file descriptor
 * Return: 1
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFF_S];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_S)
	{
		write(fd, buf, i);
			i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putsfd - prints input string
 * @str: string to be printed
 * @fd: file descriptor
 * Return: num of chars
 */
int _putsfd(char *str, int fd)
{
	int i;

	i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i = i + _putfd(*str++, fd);
	}
	return (i);

}
