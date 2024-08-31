#include "simpleshell.h"

/**
 * error_puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void error_puts(char *string)
{
	int k = 0;

	if (!string)
		return;
	while (string[k] != '\0')
	{
		error_putchar(string[k]);
		k++;
	}
}

/**
 * error_putchar - writes the character c to stderr
 * @ch: The char to print
 *
 * Return: 1 on success, -1 on error,
 * and errno is set appropriately.
 */
int error_putchar(char ch)
{
	static int buffer_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, buffer_index);
		buffer_index = 0;
	}
	if (ch != FLUSH_BUFFER)
		buffer[buffer_index++] = ch;
	return (1);
}

/**
 * _put_filed - writes the character c to given filed
 * @ch: The char to print
 * @filed: The filedescriptor to write to
 *
 * Return: 1 on success, -1 on error, and errno is set appropriately.
 */
int _put_filed(char ch, int filed)
{
	static int buffer_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(filed, buffer, buffer_index);
		buffer_index = 0;
	}
	if (ch != FLUSH_BUFFER)
		buffer[buffer_index++] = ch;
	return (1);
}

/**
 *_puts_filed - prints an input string
 * @string: the string to be printed
 * @filed: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _puts_filed(char *string, int filed)
{
	int char_count = 0;

	if (!string)
		return (0);
	while (*string)
	{
		char_count += _put_filed(*string++, filed);
	}
	return (char_count);
}
