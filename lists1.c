#include "shell.h"

/**
 * list_len - checks the length of a linked list
 * @h: pointer
 * Return: size of linked list
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}
/**
 * list_to_strings - returns an array of strings
 * @head: pointer
 * Return: string array
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char *st;
	char **sts;

	if (!head || !i)
		return (NULL);
	sts = malloc(sizeof(char *) * (i + 1));
	if (!sts)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		st = malloc(_strlen(node->str) + 1);
		if (!st)
		{
			for (j = 0; j < i; j++)
				free(sts[j]);
			free(sts);
			return (NULL);
		}

		st = _strcpy(st, node->str);
		sts[i] = st;
	}
	sts[i] = NULL;
	return (sts);
}

/**
 * print_list - prints out the linked list
 * @h: pointer
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}
/**
 * node_starts_with - returns node
 * @node: pointer
 * @prefix: string to match
 * @c: next char
 * Return: node or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *n = NULL;

	while (node)
	{
		n = starts_with(node->str, prefix);
		if (n && ((c == -1) || (*n == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - checks index of a given node
 * @head: pointer
 * @node: pointer
 * Return: index ofa node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
