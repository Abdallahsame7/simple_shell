#include "shell.h"

/**
 * add_node - Adds a node to the beginning of the list.
 * @head: Address of the pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Size of the list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_headdd;

	if (!head)
		return (NULL);
	new_headdd = malloc(sizeof(list_t));
	if (!new_headdd)
		return (NULL);
	_memset((void *)new_headdd, 0, sizeof(list_t));
	new_headdd->num = num;
	if (str)
	{
		new_headdd->str = _strdup(str);
		if (!new_headdd->str)
		{
			free(new_headdd);
			return (NULL);
		}
	}
	new_headdd->next = *head;
	*head = new_headdd;
	return (new_headdd);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of the pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Size of the list.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nodeee, *nodeee;

	if (!head)
		return (NULL);

	nodeee = *head;
	new_nodeee = malloc(sizeof(list_t));
	if (!new_nodeee)
		return (NULL);
	_memset((void *)new_nodeee, 0, sizeof(list_t));
	new_nodeee->num = num;
	if (str)
	{
		new_nodeee->str = _strdup(str);
		if (!new_nodeee->str)
		{
			free(new_nodeee);
			return (NULL);
		}
	}
	if (nodeee)
	{
		while (nodeee->next)
			nodeee = nodeee->next;
		nodeee->next = new_nodeee;
	}
	else
		*head = new_nodeee;
	return (new_nodeee);
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t iii = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		iii++;
	}
	return (iii);
}

/**
 * delete_node_at_index - Deletes the node at the given index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nodeee, *prev_nodeee;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nodeee = *head;
		*head = (*head)->next;
		free(nodeee->str);
		free(nodeee);
		return (1);
	}
	nodeee = *head;
	while (nodeee)
	{
		if (i == index)
		{
			prev_nodeee->next = nodeee->next;
			free(nodeee->str);
			free(nodeee);
			return (1);
		}
		i++;
		prev_nodeee = nodeee;
		nodeee = nodeee->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a linked list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nodeee, *next_nodeee, *headdd;

	if (!head_ptr || !*head_ptr)
		return;
	headdd = *head_ptr;
	nodeee = headdd;
	while (nodeee)
	{
		next_nodeee = nodeee->next;
		free(nodeee->str);
		free(nodeee);
		nodeee = next_nodeee;
	}
	*head_ptr = NULL;
}
