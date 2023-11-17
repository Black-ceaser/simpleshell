#include "shell.h"
/**
 * get_history_file - history of file
 * @info: argument structure
 * Return: string
 */
char *get_history_file(info_t *info)
{
	char *buff, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates files
 * @info: argument structure
 *
 * Return: 1 or -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	list_t *node = NULL;
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - checks from file history
 * @info: argument structure
 * Return: 0
 */
int read_history(info_t *info)
{
	int i = 0;
	int last = 0;
	int lc = 0;
	ssize_t fd, readlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	readlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, lc++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, lc++);
	free(buf);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - builds the histroy
 * @info: argument structure
 * @buf: buffer
 * @linecount: linecount
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history
 * @info: arguments structure
 * Return: histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->numb = a++;
		node = node->next;
	}
	return (info->histcount = a);
}























