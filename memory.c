#include "shell.h"

/**
 * bfree - free
 * @ptr: pointer
 *
 * Return: int 
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
