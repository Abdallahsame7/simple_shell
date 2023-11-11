#include "shell.h"

/**
 * _myhistory - Display the command history list, one command per line,
 *              each preceded by line numbers starting at 0.
 * @info: A structure containing potential arguments. Used to maintain a
 *        consistent function prototype.
 * 
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - Unset an alias associated with a given string.
 * @info: The parameter struct that holds alias data.
 * @str: The string representing the alias to be unset.
 * 
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *pp;
    char character;
	int ret;

	pp = _strchr(str, '=');
	if (!pp)
		return (1);
	character = *pp;
	*pp = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pp = character;
	return (ret);
}

/**
 * setAlias - Set an alias to a string.
 * @info: The parameter struct that holds alias data.
 * @str: The string representing the alias to be set.
 * 
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *ppp;

	ppp = _strchr(str, '=');
	if (!ppp)
		return (1);
	if (!*++ppp)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Print an alias string.
 * @node: The alias node containing the string to be printed.
 * 
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *p = NULL;
    char *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myalias - Simulates the behavior of the alias command (see 'man alias').
 * @info: A structure that contains potential arguments. Used to maintain
 *        a consistent function prototype.
 *  
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int ii = 0;
	char *ppp = NULL;
	list_t *node32 = NULL;

	if (info->argc == 1)
	{
		node32 = info->alias;
		while (node32)
		{
			print_alias(node32);
			node32 = node32->next;
		}
		return (0);
	}
	for (ii = 1; info->argv[ii]; ii++)
	{
		ppp = _strchr(info->argv[ii], '=');
		
        if (ppp)
			set_alias(info, info->argv[ii]);
		else
			print_alias(node_starts_with(info->alias, info->argv[ii], '='));
    }

	return (0);
}
