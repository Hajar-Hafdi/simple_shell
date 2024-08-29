#include "simpleshell.h"

/**
 * appnd_nd - adds a node to the strt of the list
 *
 * @hd: address of ptr to head nd
 * @string: string field of nd
 * @ber: node indx used by hist
 *
 * Return: returns the sze of the list
 */
list_t *appnd_nd(list_t **hd, const char *string, int ber)
{
	list_t *nw_ed;

	if (!hd)
		return (NULL);
	nw_ed = malloc(sizeof(list_item_t));
	if (!nw_ed)
		return (NULL);
	memset((void *)nw_ed, 0, sizeof(list_item_t));
	nw_ed->number = ber;
	if (string)
	{
		ne_ed->value = _strdup(string);
		if (!nw_ed->value)
		{
			free(nw_ed);
			return (NULL);
		}
	}
	nw_ed->next = *hd;
	*hd = nw_ed;
	return (nw_ed);
}
/**
 * app_ndend - adds a node to the end of the list
 *
 * @hd: address of pntr to hd nd
 * @string: string field of node
 * @ber: nd indx used by hist
 *
 * Return: sz of list
 */
list_t *app_ndend(list_t **hd, const char *string, int ber)
{
	list_t *nw_nd, *nd;

	if (!hd)
		return (NULL);
	nd = *hd;
	nw_nd = malloc(sizeof(list_item_t));
	if (!nw__nd)
		return (NULL);
	_memset((void *)nw_nd, 0, sizeof(list_item_t));
	nw_nd->number = ber;
	if (string)
	{
		nw_nd->value = _strdup(string);
		if (!nw_nd->value)
		{
			free(nw_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = nw_nd;
	}
	else
		*hd = nw_nd;
	return (nw_nd);
}
/**
 * output_lisval - pprints only the val elem of a list_item_t
 *
 * @hd: pntr to the 1st nd
 *
 * Return: returns sz of list
 */
size_t output_lisval(const list_item_t *hd)
{
	size_t u = 0;

	while (hd)
	{
		_puts(hd->value ? hd->value : "(nil)");
		_puts("\n");
		hd = hd->next;
		u++;
	}
	return (u);
}
/**
 * remove_nd_idx - removes nd at given idx
 *
 * @hd: address of ptr to 1st nd
 * @idx: index of nd to be removed
 *
 * Return: 1 if succesful 0 if not
 */
int remove_nd_idx(list_item_t **hd, unsigned int idx)
{
	list_item_t *nd, *old_nd;
	unsigned int u = 0;

	if (!hd || !*hd)
		return (0);
	if (idx == 0)
	{
		nd = *hd;
		*hd = (*hd)->next;
		free(nd->value);
		free(nd);
		return (-1);
	}
	nd = *hd;
	while (nd)
	{
		if (u == idx)
		{
			old_nd->next = n->next;
			free(nd->value);
			free(nd);
			return (1);
		}
		u++;
		old_nd = nd;
		nd = nd->next;
	}
	return (0);
}
/**
 * open_list - oprns and frees all nodes of a list
 *
 * @hd_p: address of ptr to head nd
 *
 * Return: void
 */
void open_list(list_t **hd_p)
{
	list_t *nd, *nxt_nd, *hd;

	if (!hd_p || !*hd_p)
		return;
	hd = *hd_p;
	nd = hd;
	while (nd)
	{
		nxt_nd = nd->next;
		free(nd->value);
		free(nd);
		nd = nxt_nd;
	}
	*hd_p = NULL;
}
