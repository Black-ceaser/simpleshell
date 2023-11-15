#include "shell.h"

/**
 * _erratoi - conv strings to int
 * @s: sting to be conv
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int reslt = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			reslt *= 10;
			reslt += (s[i] - '0');
			if (reslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (reslt);
}

/**
 * print_error - prints an error message
 * @info: info stuct
 * @estr: sting containing specified error type
 * Return: 0 or -1
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - prints decimal numbers
 * @input: input
 * @fd: file descriptor
 * Return: charcters to be printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a = 0;
	int count = 0;
	unsigned int _abs_;
	unsigned int current;

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
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
				count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * convert_number - function for convetting
 * @num: number
 * @base: base
 * @flags: arg flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	char *pt;
	char sign = 0;
	static char buffer[50];
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';
	do {
		*--pt = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--pt = sign;
	return (pt);
}




