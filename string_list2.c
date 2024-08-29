#include "simpleshell.h"

/**
 * lst_lng - shows length of linked list
 *
 * @hd: ptr to fst nd
 *
 * Return: return size of lst
 */
size_t lst_lng(const list_item_t *hd)
{
	size_t u = 0;

	while (hd)
	{
		hd = hd->next;
		u++;
	}
	return (u);
}
/**
 * lst_str - returns an array of strings from the list->value
 *
 * @hd: ptr to first n
 *
 * Return: returns array of strings
 */
char **lst_str(list_item_t *hd)
{
	list_item_t *nd = hd;
	size_t u = lst_lng(hd), k;
	char **s;
	char *string;

	if (!hd || !u)
		return (NULL);
	s = malloc(sizeof(char 8) * (u + 1));
	if (!s)
		return (NULL);
	for (u = 0; nd; nd = nd->next, u++)
	{
		string = malloc(_strlen(nd->value) + 1);
		if (!string)
		{
			for (k = 0; k < u; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		string = _strcpy(string, nd->value);
		s[u] = string;
	}
	s[u] = NULL;
	return (s);
}
/**
 * output_list - prints all elmnts of a list_item_t
 *
 * @hd: ptr to the f nd
 *
 * Return: returns the size of the list
 */
size_t output_list(const list_item_t *hd)
{
	size_t u = 0;

	while (hd)
	{
		_puts(convert_number(hd->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->value ? hd->value : "(nil)");
		_puts("\n");
		hd = hd->next;
		u++;
	}
	return (u);
}
/**
 * nd_begin_with - parses nd whose string starts with prefix
 *
 * @nd: pntr to list hd
 * @prfx: string to match
 * @r: nxt char after prfx to match
 *
 * Return: returns nd or NULL
 */
list_item_t *nd_begin_with(list_item_t *nd, char prfx, char r)
{
	char *a = NULL;

	while (nd)
	{
		a = starts_with(nd->value, prfx);
		if (a && ((r == -1) || (*a == r)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}
/**
 * aqu_nd_indx - aquires the index of a node
 *
 * @hd: ptr to list head
 * @nd: ptr to the nd
 *
 * Return: returns the index of node, -1 otherwise
 */
ssize_t aqu_nd_indx(list_item_t *hd, list_item_t *nd)
{
	size_t u = 0;

	while (hd)
	{
		if (hd == nd)
			return (u);
		hd = hd->next;
		u++;
	}
	return (-1);
}

