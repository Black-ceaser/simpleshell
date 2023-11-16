#include "shell.h"

/**
 * add_node - adds node to start of a string
 * @head: poiner to the head
 * @str: str field
 * @numb: node index
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int numb)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->numb = numb;
	if (str)
	{
		new_h->str = strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_node_end - adds to the end of a list
 * @head: pointer to the head
 * @str: str field
 * @num: node index
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int numb)
{
	list_t *newn;
	list_t *node;

	if (!head)
		return (NULL);
	node = *head;
	newn = malloc(sizeof(list_t));
	if (!newn)
		return (NULL);
	_memset((void *)newn, 0, sizeof(list_t));
	newn->numb = numb;
	if (str)
	{
		newn->str = _strdup(str);
		if (!newn->str)
		{
			free(newn);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newn;
	}
	else
		*head = newn;
	return (newn);
}


/**print_list_str - prints str elements of list_t
 * @h: address of first node
 * Return: list size
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * delete_node_at_index - deletes node
 * @head: pointer to the head
 * @index: id of node to be deleted
 * Return: 1 or 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);
	if (index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	whle (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			node = node->next;
		}
	}
	return (0);
}







