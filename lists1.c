#include "shell.h"

/**
 * list_len - determines length
 * @h: points to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t d = 0;

	while (h)
	{
		h = h->next;
		d++;
	}
	return (d);
}

/**
 * list_to_strings - array of strings
 * @head: points to first node
 * Return: strings in array
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t d = list_len(head), c;
	char **strs;
	char *str;

	if (!head || !d)
		return (NULL);
	strs = malloc(sizeof(char *) * (d + 1));
	if (!strs)
		return (NULL);
	for (d = 0; node; node = node->next, d++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (c = 0; c < d; c++)
				free(strs[c]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[d] = str;
	}
	strs[d] = NULL;
	return (strs);
}


/**
 * print_list - displays all elements
 * @h: points to first node
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t d = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		d++;
	}
	return (d);
}

/**
 * node_starts_with - returns node with prefix
 * Return: match node or null
 * @prefix: matching string
 * @c: next character
 * @node: points to head
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - fetches index node
 * @head: points head
 * @node: points node
 * Return: index or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t d = 0;

	while (head)
	{
		if (head == node)
			return (d);
		head = head->next;
		d++;
	}
	return (-1);
}
