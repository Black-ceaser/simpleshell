#include "shell.h"

/**
 * is_cmd - detemines whether a file is executable
 * @info: argument structure
 * @path: path
 * Return: 1 or 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - duplicates chars
 * @pathstr: path
 * @start: first index
 * @stop: stop index
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0;
	int i = 0;

	for (i = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[i++] = pathstr[j];
	buf[i] = 0;
	return (buf);
}

/**
 * find_path - finds cmd in string path
 * @info: argument structure
 * @pathstr: path
 * @cmd: cmd
 * Return:path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0;
	int currp = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, currp, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			currp = j;
		}
		j++;
	}

	return (NULL);
}
