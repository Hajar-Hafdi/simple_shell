#include "simpleshell.h"

/**
 * is_interactive - checks if shell is interactive mode
 * @shell_info: struct address
 *
 * Return: 1 if interactive mode, 0 if not
 */
int is_interactive(shell_info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->input_fd <= 2);
}

/**
 * is_delimeter - checks if the character is a delimeter
 * @c: the character to check
 * @d: the delimeter
 * Return: 1 if true, 0 otherwise
 */
int is_delimeter(char c, char *d)
{
	while (*d)
		if (*d++ == c)
			return (1);
	return (0);
}

/**
 * error_atoi - Convert a string to an integer.
 * @str: The input string.
 * Return: The integer value if 1, or -1 on error.
 */
int error_atoi(const char *str)
{
	unsigned long int result = 0;
	int k = 0;

	if (*str == '+')
		str++;
	for (k = 0; str[k] != '\0'; k++)
	{
		if (str[k] >= '0' && str[k] <= '9')
		{
			result *= 10;
			result += (str[k] - 48);
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * output_error - prints an error message
 * @shell_info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void output_error(shell_info_t *shell_info, char *estr)
{
	error_puts(shell_info->program_name);
	error_puts(": ");
	print_d(shell_info->exec_count, STDERR_FILENO);
	error_puts(": ");
	error_puts(shell_info->args[0]);
	error_puts(": ");
	error_puts(estr);
}

/**
 * print_decimal - function prints a integer number (base 10)
 * @input: the input
 * @filed: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int filed)
{
	int (*__put_char)(char) = _put_char;
	unsigned int _absolute, current_num;
	int num, count = 0;

	if (filed == STDERR_FILENO)
		__put_char = error_putchar;
	if (input < 0)
	{
		_absolute = -input;
		__put_char('-');
		count++;
	}
	else
		_absolute = input;
	current_num = _absolute;
	for (num = 1000000000; num > 1; num /= 10)
	{
		if (_absolute / num)
		{
			__put_char('0' + current_num / num);
			count++;
		}
		current_num %= num;
	}
	__put_char('0' + current_num);
	count++;

	return (count);
}
