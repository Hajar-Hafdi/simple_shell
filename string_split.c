#include "simpleshell.h"
/**
 * **split_string - splits a string into words.
 * Repeat delimiters are ignored
 * @string: the input string
 * @delim: the delimiter string
 * Return: a pointer to an array of strings, NULL on failure
 */
char **split_string(char *string, char *delim)
{
	int index, count, len, wd_index, total_words = 0;
	char **array;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (index = 0; string[index] != '\0'; index++)
		if (!is_delimeter(string[index], delim) &&
		(is_delimeter(string[index + 1], delim) || !string[index + 1]))
		{
			total_words++;
		}
	if (total_words == 0)
		return (NULL);
	array = malloc((1 + total_words) * sizeof(char *));
	if (!array)
		return (NULL);
	for (index = 0, count = 0; count < total_words; count++)
	{
		while (is_delimeter(string[index], delim))
			index++;
		len = 0;
		while (!is_delimeter(string[index + len], delim) && string[index + len])
			len++;
		array[count] = malloc((len + 1) * sizeof(char));
		if (!array[count])
		{
			for (wd_index = 0; wd_index < count; wd_index++)
				free(array[wd_index]);
		free(array);
		return (NULL);
		}
	for (wd_index = 0; wd_index < len; wd_index++)
		array[count][wd_index] = string[index++];
	array[count][wd_index] = 0;
	}
	array[count] = NULL;
	return (array);
}
