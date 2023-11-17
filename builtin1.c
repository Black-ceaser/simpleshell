#include "shell.h"

/**
 * _myhistory - shows history
 * @info: argument structure
 * Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias
 * @info: arugment struct
 * @str: string alias
 * Return: 0 or 1
 */
int unset_alias(info_t *info, char *str)
{
	char *p;
	char a;
	int rett;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	a = *p;
	*p = 0;
	rett = delete_node_at_index(&(info->alias),
			get_node_index(info->alias,
				node_starts_with(info->alias, str, -1)));
	*p = a;
	return (rett);
}

/**
 * set_alias - sets alias
 * @info: argument struct
 * @str: string alias
 * Return: 0 or 1
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints alias
 * @node: alias node
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *p = NULL;
	char *c = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (c = node->str; c <= p; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _myalias - replica of alias builtin
 * @info: argument structure
 * Return: 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *pt = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		pt = _strchr(info->argv[a], '=');
		if (pt)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}
	return (0);
}








































