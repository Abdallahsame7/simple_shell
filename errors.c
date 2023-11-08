#include "shell.h"

/**
 * _eputs - Print a string to the standard error stream (stderr).
 * @str: The string to be printed.
 * Return: None.
 */
void _eputs(char *str)
{
	int iii = 0;

	if (!str)
		return;
	while (str[iii] != '\0')
	{
		_eputchar(str[iii]);
		iii++;
	}
}

/**
 * _eputchar - Write a character to stderr.
 * @c: The character to write.
 * Return: 1 on success, -1 on error (errno is set appropriately).
 */
int _eputchar(char c)
{
	static int iiii;
	static char buffff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH)
	{
		write(2, buffff, iiii);
		iiii = 0;
	}
    if(iiii >= WRITE_BUF_SIZE)
	{
		write(2, buffff, iiii);
		iiii = 0;
	}
	if (c != BUF_FLUSH)
		buffff[iiii++] = c;
	return (1);
}

/**
 * _putfd - Write a character to the specified file descriptor.
 * @c: The character to write.
 * @fd: The file descriptor to write to.
 * Return: 1 on success, -1 on error (errno is set appropriately).
 */
int _putfd(char c, int fd)
{
	static int iiii;
	static char bufff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH ) 
    {
		write(fd, bufff, iiii);
		iiii = 0;
	}
    if (iiii >= WRITE_BUF_SIZE)
	{
		write(fd, bufff, iiii);
		iiii = 0;
	}
	if (c != BUF_FLUSH)
		bufff[iiii++] = c;
	return (1);
}

/**
 * _putsfd - Print a string to a specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int iuu = 0;

	if (!str)
		return (0);
	while (*str)
	{
		iuu += _putfd(*str++, fd);
	}
	return (iuu);
}
