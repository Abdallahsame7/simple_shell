#include "shell.h"

/**
 * _myenv - Print the current environment.
 * @info: Structure containing potential arguments.
 * 
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: A structure containing potential arguments.
 * @name: The name of the environment variable.
 * 
 * Return: The value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node343 = info->env;
	char *pppp;

	while (node343)
	{
		pppp = starts_with(node->str, name);
		if (pppp && *pppp)
			return (pppp);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize or modify an environment variable.
 * @info: Structure containing potential arguments.
 *  
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *  
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int iiii;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (iiii = 1; iiii <= info->argc; iiii++)
		_unsetenv(info, info->argv[iiii]);

	return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node32131 = NULL;
	size_t iiii;

	for (iiii = 0; environ[iiii]; iiii++)
		add_node_end(&node32131, environ[iiii], 0);
	info->env = node32131;
	return (0);
}
