#include "shell.h"

/**
 * is_chain - test
 * @info: parameter struct
 * @buf: char
 * @p: address buf
 *
 * Return: int
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t l = *p;

	if (buf[l] == '|' && buf[l + 1] == '|')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[l] == '&' && buf[l + 1] == '&')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[l] == ';') /* found end of this command */
	{
		buf[l] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = l;
	return (1);
}

/**
 * check_chain - checks
 * @info: parameter
 * @buf:char buffer
 * @p: add
 * @i: starting
 * @len: length of buf
 *
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t l = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			l = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			l = len;
		}
	}

	*p = l;
}

/**
 * replace_alias - replacess
 * @info: infooo
 *
 * Return: int
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *nodo;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		nodo = node_starts_with(info->alias, info->argv[0], '=');
		if (!nodo)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(nodo->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - replaces
 * @info: the parameter struct
 *
 * Return: int
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *nodo;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nodo = node_starts_with(info->env, &info->argv[i][1], '=');
		if (nodo)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(nodo->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address
 * @new: new string
 *
 * Return: int
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
