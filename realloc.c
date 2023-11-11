#include "shell.h"

/**
 **_memset - fills
 *@s: the pointer 
 *@b: char
 *@n: int
 *Return: char
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * ffree - frees
 * @pp: string
 */
void ffree(char **pp)
{
	char **v = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(v);
}

/**
 * _realloc - reallocates
 * @ptr: pointer
 * @old_size: byte size
 * @new_size: byte size new
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pol;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pol = malloc(new_size);
	if (!pol)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pol[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pol);
}
