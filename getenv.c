#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables as a string array.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: A string array containing a copy of the environment variables.
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
 * _unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments, used to maintain
 *        a constant function prototype.
 * @var: The string representing the environment variable property.
 * Return: 1 if the variable is successfully deleted, 0 otherwise.
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
			info->env_changed = delete_node_at_index(&(info->env), i);
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
