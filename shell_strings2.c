#include "simpleshell.h"

/**
 * _str_copy - copies a string
 * @desti: the destination
 * @sorc: the source
 *
 * Return: pointer to destination
 */
char *_str_copy(char *desti, char *sorc)
{
	int num = 0;

	if (desti == sorc || sorc == 0)
		return (desti);
	while (sorc[num])
	{
		desti[num] = sorc[num];
		num++;
	}
	desti[num] = 0;
	return (desti);
}

/**
 * _strd_up - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strd_up(const char *string)
{
	int k, length = 0;
	char *dupl;
	const char *temp = string;

	if (string == NULL)
		return (NULL);
	while (*temp++)
		length++;
	dupl = malloc(sizeof(char) * (length + 1));
	if (!dupl)
		return (NULL);
	for (k = 0; k < length; k++)
		dupl[k] = string[k];
	dupl[length] = '\0';
	return (dupl);
}

/**
 * _str_cmp - the comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: positive if str1 > str2, zero if str1 == str2,
 * negative if str1 < str2
 */
int _str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
 * start_with - check if the needle starts with haystack
 * @hstack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next char of haystack or NULL
 */
char *start_with(const char *hstack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * _str_cat - concatenates two strings
 * @desti: the destination string
 * @sorc: the source string
 *
 * Return: pointer to destination buffer
 */
char *_str_cat(char *desti, char *sorc)
{
	char *ret = desti;

	while (*desti)
		desti++;
	while (*sorc)
		*desti++ = *sorc++;
	*desti = *sorc;
	return (ret);
}
