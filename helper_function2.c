#include "simpleshell.h"

/**
 * convert_num - converter function, a clone of itoa
 * @n: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int n, int base, int flags)
{
	static char *cvt_arr;
	static char buff[50];
	char sign = 0;
	char *pointer;
	unsigned long num = n;

	if (!(flags & CONVERT_TO_UNSIGNED) && n < 0)
	{
		num = -n;
		sign = '-';

	}
	cvt_arr = flags & CONVERT_TO_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buff[49];
	*pointer = '\0';

	do {
		*--pointer = cvt_arr[num % base];
		num /= base;
	} while (num != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * remove_comm - replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comm(char *buffer)
{
	int idx;

	for (idx = 0; buffer[idx] != '\0'; idx++)
		if (buffer[idx] == '#' && (!idx || buffer[idx - 1] == ' '))
		{
			buffer[idx] = '\0';
			break;
		}
}
