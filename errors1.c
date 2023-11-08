#include "shell.h"

/**
 * _erratoi - Convert a string to an integer.
 * @s: The string to be converted.
 * Return: The converted number if successful, 0 if no numbers in the string, or -1 on error.
 */
int _erratoi(char *s)
{
	int iuu = 0;
	unsigned long int results = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (iuu = 0;  s[iuu] != '\0'; iuu++)
	{
		if (s[iuu] >= '0' && s[iuu] <= '9')
		{
			results *= 10;
			results += (s[iuu] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_error - Print an error message to stderr.
 * @info: The parameter and return info struct (potentially unused).
 * @estr: The string containing the specified error type.
 * Return: None.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Print a decimal (integer) number (base 10).
 * @input: The input number to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int iee, countee = 0;
	unsigned int _abs_, currenting;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		countee++;
	}
	else
		_abs_ = input;
	currenting = _abs_;
	for (iee = 1000000000; iee > 1; iee /= 10)
	{
		if (_abs_ / iee)
		{
			__putchar('0' + currenting / iee);
			countee++;
		}
		currenting %= iee;
	}
	__putchar('0' + currenting);
	countee++;

	return (countee);
}

/**
 * convert_number - Convert a number to a string.
 * @num: The number to convert.
 * @base: The base of the conversion.
 * @flags: Argument flags.
 * 
 * Return: The resulting string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arrayyy;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		signnn = '-';

	}
	arrayyy = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arrayyy[n % base];
		n /= base;
	} while (n != 0);

	if (signnn)
		*--ptr = signnn;
	return (ptr);
}

/**
 * remove_comments - Replace the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 * Return: Always 0.
 */
void remove_comments(char *buf)
{
	int iiie;

	for (iiie = 0; buf[iiie] != '\0'; iiie++)
		if (buf[iiie] == '#' && (!iiie || buf[iiie - 1] == ' '))
		{
			buf[iiie] = '\0';
			break;
		}
}
