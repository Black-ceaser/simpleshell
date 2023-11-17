#include "shell.h"

/**
 * clear_info - info_t initializes
 * @info: argument struture
 * Return: void
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argv = 0;
}

/**
 * set_info - info_t initializes
 * @info: argument structure
 * @av: argument vector
 * Return: void
 */
void set_info(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->argv)
	{
		info->argv = strtow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
		{
			info->argv[0] = _strdup(info->arg);
			info->argv[1] = NULL;
		}
	}
	for (a = 0; info->argv && info->argv[a]; a++)
		;
	info->argc = a;

	replace_alias(info);
	replace_vars(info);
	}
}

/**
 * free_info - free argument structure
 * @info: argument structure
 * @all: all fields
 * Return: void
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **) info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
