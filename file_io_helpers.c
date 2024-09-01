#include "simpleshell.h"

/**
 * retrieve_hist - get the history file path
 *
 * @sdata: ptr to shell info structure
 *
 * Return: allocated string having hist file path
 */
char *retrieve_hist(shellinfo_t *sdata)
{
	char *buff, *home_dirct;

	home_dirct = get_envval(sdata, "HOME=");
	if (!home_dirct)
		return (NULL);
	buff = malloc(sizeof(char) *
			(_str_length(home_dirct) + _str_length(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_str_copy(buff, home_dirct);
	_str_cat(buff, "/");
	_str_cat(buff, HISTORY_FILE);
	return (buff);
}
/**
 * w_hist - creates or adds to history filr
 *
 * @sdata: ptr to shell inf struct
 *
 * Return: 1 if successful, 0 if not
 */
int w_hist(shellinfo_t *sdata)
{
	ssize_t filed;
	char *filenm = retrieve_hist(sdata);
	list_item_t *node = NULL;

	if (!filenm)
		return (-1);
	filed = open(filenm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenm);
	if (filed == -1)
		return (-1);
	for (node = sdata->cmd_history; node; node = node->next)
	{
		_puts_filed(node->value, filed);
		_put_filed('\n', filed);
	}
	_put_filed(FLUSH_BUFFER, filed);
	close(filed);

	return (1);
}
/**
 * add_to_history - appends an entry to hist
 *
 * @sdata: ptr to shell info strct
 * @buff: buffer having hist entry
 * @linec: line count of hist rntry
 *
 * Return: always 0 (Success)
 */
int add_to_history(shellinfo_t *sdata, char *buff, int linec)
{
	list_item_t *nod = NULL;

	if (sdata->cmd_history)
		nod = sdata->cmd_history;
	app_ndend(&nod, buff, linec);
	if (!sdata->cmd_history)
		sdata->cmd_history = nod;
	return (0);
}
/**
 * updhistory_num - remmebers the history linked list after chgs
 *
 * @sdata: ptr to shell info struct
 *
 * Return: returns new hist count
 */
int updhistory_num(shellinfo_t *sdata)
{
	list_item_t *nod = sdata->cmd_history;
	int u = 0;

	while (nod)
	{
		nod->number = u++;
		nod = nod->next;
	}
	return (sdata->history_count = u);
}
/**
 * r_hist - reads hist from a file
 *
 * @sdata: ptr to shell info struct
 *
 * Return: the num of entries in hist
 */
int r_hist(shellinfo_t *sdata)
{
	int u, linec = 0, last = 0;
	ssize_t fld, rdlenn, fz = 0;
	struct stat st;
	char *buff = NULL, *filenm = retrieve_hist(sdata);

	if (!filenm)
		return (0);
	fld = open(filenm, O_RDONLY);
	free(filenm);
	if (fld == -1)
		return (0);
	if (!fstat(fld, &st))
		fz = st.st_size;
	if (fz < 2)
		return (0);
	buff = malloc(sizeof(char) * (fz + 1));
	if (!buff)
		return (0);
	rdlenn = read(fld, buff, fz);
	buff[fz] = 0;
	if (rdlenn <= 0)
		return (free(buff), 0);
	close(fld);
	for (u = 0; u < fz; u++)
		if (buff[u] == '\n')
		{
			buff[u] = 0;
			add_to_history(sdata, buff + last, linec++);
			last = u + 1;
		}
	if (last != u)
		add_to_history(sdata, buff + last, linec++);
	free(buff);
	sdata->history_count = linec;
	while (sdata->history_count-- >= MAXIMUM_HISTORY_ENTERIES)
		remove_nd_idx(&(sdata->cmd_history), 0);
	updhistory_num(sdata);
	return (sdata->history_count);
}
