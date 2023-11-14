#include "shell.h"

/**
 * **strtow - spliting
 * @str:  input string
 * @d: delimeter string
 * Return: NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, kk, mm, num = 0;
	char **h;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	h = malloc((1 + num) * sizeof(char *));
	if (!h)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[i], d))
			i++;
		kk = 0;
		while (!is_delim(str[i + kk], d) && str[i + kk])
			kk++;
		h[j] = malloc((kk + 1) * sizeof(char));
		if (!h[j])
		{
			for (kk = 0; kk < j; kk++)
				free(h[kk]);
			free(h);
			return (NULL);
		}
		for (mm = 0; mm < kk; mm++)
			h[j][mm] = str[i++];
		h[j][mm] = 0;
	}
	h[j] = NULL;
	return (h);
}

/**
 * **strtow2 - string
 * @str: input string
 * @d: delimeter
 * Return: pointer
 */
char **strtow2(char *str, char d)
{
	int i, j, kk, mm, num = 0;
	char **h;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	h = malloc((1 + num) * sizeof(char *));
	if (!h)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		kk = 0;
		while (str[i + kk] != d && str[i + kk] && str[i + kk] != d)
			kk++;
		h[j] = malloc((kk + 1) * sizeof(char));
		if (!h[j])
		{
			for (kk = 0; kk < j; kk++)
				free(h[kk]);
			free(h);
			return (NULL);
		}
		for (mm = 0; mm < kk; mm++)
			h[j][mm] = str[i++];
		h[j][mm] = 0;
	}
	h[j] = NULL;
	return (h);
}
