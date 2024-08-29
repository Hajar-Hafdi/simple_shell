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
		_error_putchar(string[k]);
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
	static int num;
	static char buffer[INPUT_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || num >= INPUT_BUFFER_SIZE)
	{
		write(2, buffer, num);
		num = 0;
	}
	if (ch != FLUSH_BUFFER)
		buffer[num++] = ch;
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
	static int k;
	static char buf[INPUT_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || k >= INPUT_BUFFER_SIZE)
	{
		write(filed, buf, k);
		k = 0;
	}
	if (ch != FLUSH_BUFFER)
		buf[k++] = ch;
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
	int k = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _put_filed(*string++, filed);
	}
	return (i);
}
