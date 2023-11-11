#include "shell.h"

/**
 * _strcpy - a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string duplicate
 *
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int l = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
		r[l] = *--str;
	return (r);
}

/**
 *_puts - prints input
 *@str: the string
 *
 * Return: Noth
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - writes
 * @c: The character
 *
 * Return: int
 */
int _putchar(char c)
{
	static int xx;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || xx >= WRITE_BUF_SIZE)
	{
		write(1, buf, xx);
		xx = 0;
	}
	if (c != BUF_FLUSH)
		buf[xx++] = c;
	return (1);
}
