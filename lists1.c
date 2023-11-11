#include "shell.h"

/**
 * list_len - li 
 * @h: pointer 
 *
 * Return: siz
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - array 
 * @head: pointer 
 *
 * Return: array 
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), j;
	char **st;
	char *s;

	if (!head || !x)
		return (NULL);
	st = malloc(sizeof(char *) * (x + 1));
	if (!st)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		s = malloc(_strlen(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < x; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}

		s = _strcpy(s, node->s);
		st[x] = s;
	}
	st[x] = NULL;
	return (st);
}


/**
 * print_list - all
 * @h: pointer 
 *
 * Return: siz
 */
size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - node
 * @node: pointer 
 * @prefix: string 
 * @c: next character 
 * 
 *  Return: or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - index
 * @head: pointer
 * @node: pointer
 *
 * Return: index of node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t y = 0;

	while (head)
	{
		if (head == node)
			return (y);
		head = head->next;
		y++;
	}
	return (-1);
}
