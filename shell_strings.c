#include "simpleshell.h"

/**
 *_puts - prints an input string
 *@string: the string to be printed
 *
 * Return: void
 */
void _puts(char *string)
{
	int num = 0;

	if (!string)
		return;
	while (string[num] != '\0')
	{
		_put_char(string[num]);
		num++;
	}
}

/**
 * _put_char - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _put_char(char ch)
{
	static int num;
	static char buffer[OUTPUT_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || num >= OUTPUT_BUFFER_SIZE)
	{
		write(1, buffer, num);
		num = 0;
	}
	if (ch != FLUSH_BUFFER)
		buffer[num++] = ch;
	return (1);
}

/**
 * _str_length - returns the length of a string
 * @str: the string to check
 *
 * Return: number type integer length of string
 */
int _str_length(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}
