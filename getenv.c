#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
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
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nodeee = info->env;
	size_t iii = 0;
	char *ppp;

	if (!nodeee || !var)
		return (0);

	while (nodeee)
	{
		ppp = starts_with(nodeee->str, var);
		if (ppp && *ppp == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), iii);
			iii = 0;
			nodeee = info->env;
			continue;
		}
		nodeee = nodeee->next;
		iii++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *bufff = NULL;
	list_t *nodeee;
	char *ppp;

	if (!var || !value)
		return (0);

	bufff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!bufff)
		return (1);
	_strcpy(bufff, var);
	_strcat(bufff, "=");
	_strcat(bufff, value);
	nodeee = info->env;
	while (nodeee)
	{
		ppp = starts_with(nodeee->str, var);
		if (ppp && *ppp == '=')
		{
			free(nodeee->str);
			nodeee->str = bufff;
			info->env_changed = 1;
			return (0);
		}
		nodeee = nodeee->next;
	}
	add_node_end(&(info->env), bufff, 0);
	free(bufff);
	info->env_changed = 1;
	return (0);
}
