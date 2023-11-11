#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified number of characters.
 * @dest: The destination string to which the copy is made.
 * @src: The source string from which characters are copied.
 * @n: The number of characters to be copied.
 * Return: The modified destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int iii, jjj;
	char *sss = dest;

	iii = 0;
	while (src[iii] != '\0' && iii < n - 1)
	{
		dest[iii] = src[iii];
		iii++;
	}
	if (iii < n)
	{
		jjj = iii;
		while (jjj < n)
		{
			dest[jjj] = '\0';
			jjj++;
		}
	}
	return (sss);
}

/**
 * _strncat - Concatenates two strings up to a specified number of bytes.
 * @dest: The first string, and the destination for the concatenation.
 * @src: The second string, providing characters to be appended.
 * @n: The maximum number of bytes to be used for concatenation.
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int iii, jjj;
	char *sss = dest;

	iii = 0;
	jjj = 0;
	while (dest[iii] != '\0')
		iii++;
	while (src[jjj] != '\0' && jjj < n)
	{
		dest[iii] = src[jjj];
		iii++;
		jjj++;
	}
	if (jjj < n)
		dest[iii] = '\0';
	return (sss);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */

char *_strchr(char *s, char c)
{
	char *fff = s;
	do {
		if (*fff == c)
			return fff;
	} while (*fff++ != '\0');

	return (NULL);
}
