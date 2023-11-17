#include "shell.h"
/**
 * input_buf - chains commands
 * @info: argument structure
 * @buf: buffer address
 * @len: len var address
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signHand);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets line
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;

		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;

			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));

		*buf_p = buf;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);

}

/**
 * read_buf - reads a buffer
 * @info: argument parameter
 * @buf: buffer
 * @i: size
 * Return: a
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUFF_S);
	if (a >= 0)
		*i = a;
	return (a);
}
/**
 * _getline - gets the next line from STDIN
 * @info: argument structure
 * @ptr: addres of pointer buffer
 * @length: size of ptr buffer
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_S];
	static size_t i;
	static size_t lent;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	size_t k;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == lent)
		i = lent = 0;
	r = read_buf(info, buf, &lent);
	if (r == -1 || (r == 0 && lent == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int) (c - buf) : lent;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i + 1);
	else
		strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * signHand - blocks ctr c
 * @sig_num: signal number
 * Return: void
 */
void signHand(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
















