#include "shell.h"

/**
 * intrctiv - checks if the shell is in interactive mode
 * @info: struct address
 * Return: 1 if in the shell is in interactive mode
 */
int intrctiv(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _isalpha -  checks the alphabetic character
 * @c: character input
 * Return: 1 if the character is an alphabet
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * is_delim - checks if it is a delimeter
 * @c: char to check
 * @delim: delimiter string
 * Return: 1 or 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _atoi - converts sting to integer
 * @s: string to be converted
 * Return: 0 if there is no number
 */
int _atoi(char *s)
{
	int a;
	int sign = 1;
	int flag = 0;
	int output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;
		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
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

