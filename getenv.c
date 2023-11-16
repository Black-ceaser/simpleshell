#include "shell.h"

/**
 * _unsetenv - remove env variable
 * @info: argument structure
 * @var: string env var property
 * Return: 1 or 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
				i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * get_environ - prints string of array of environ
 * @info: argument structure
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _setenv - initialize new environment variable
 * @info: argument structure
 * @var: string env var property
 * @value: the string env var value
 * Return:0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff;
	list_t *node;
	char *p;

	buff = NULL;

	if (!var || !value)
		return (0);
	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}














