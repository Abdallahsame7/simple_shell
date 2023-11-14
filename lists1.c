#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first nodeee
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t iii = 0;

	while (h)
	{
		h = h->next;
		iii++;
	}
	return (iii);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first nodeee
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nodeee = head;
	size_t iii = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !iii)
		return (NULL);
	strs = malloc(sizeof(char *) * (iii + 1));
	if (!strs)
		return (NULL);
	for (iii = 0; nodeee; nodeee = nodeee->next, iii++)
	{
		str = malloc(_strlen(nodeee->str) + 1);
		if (!str)
		{
			for (j = 0; j < iii; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nodeee->str);
		strs[iii] = str;
	}
	strs[iii] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first nodeee
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t iii = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		iii++;
	}
	return (iii);
}

/**
 * nodeee_starts_with - returns nodeee whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ppp = NULL;

	while (node)
	{
		ppp = starts_with(node->str, prefix);
		if (ppp && ((c == -1) || (*ppp == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_nodeee_index - gets the index of a nodeee
 * @head: pointer to list head
 * @node: pointer to the nodeee
 *
 * Return: index of nodeee or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t iii = 0;

	while (head)
	{
		if (head == node)
			return (iii);
		head = head->next;
		iii++;
	}
	return (-1);
}
