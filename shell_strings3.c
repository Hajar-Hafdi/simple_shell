#include "simpleshell.h"

/**
 **_strn_cpy - copies a string
 *@desti: the destination string to be copied to
 *@sorc: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strn_cpy(char *desti, char *sorc, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		desti[i] = sorc[i];

	for (; i < n; i++)
		desti[i] = '\0';

	return (desti);
}

/**
 **_strn_cat - concatenates two strings
 *@desti: the first string
 *@sorc: the second string
 *@n: the maximum number of char to be appended
 *Return: the concatenated string
 */
char *_strn_cat(char *desti, char *sorc, int n)
{
	int len = 0, j = 0;
	char *str = desti;

	while (desti[len] != '\0')
		len++;
	while (sorc[j] != '\0' && j < n)
	{
		desti[len] = sorc[j];
		len++, j++;
	}

	desti[len] = '\0';

	return (str);
}

/**
 **_str_chr - locates a character in a string
 *@str: the string to be parsed
 *@ch: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *_str_chr(char *str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
			return (str);
	str++;
	}
	return (NULL);
}
