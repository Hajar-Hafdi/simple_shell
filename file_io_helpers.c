#include "simpleshell.h"

/**
 * retrieve_hist - get the history file path
 *
 * @sdata: ptr to shell info structure
 *
 * Return: allocated string having hist file path
 */
char retrieve_hist(shell_info_t *sdata)
{
	char *buff, *home_dirct;

	home_dirct = _getenv(sdata, "HOME=");
	if (!home_dirct)
		return (NULL);
	buff = malloc(sizeof(char) *
			(_strlen(home_dirct) + _strlen(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, home_dirct);
	_strcat(buff, "/");
	_strcat(buff, HISTORY_FILE);
	return (buff);
}
/**
 * preserve_hist - creates or adds to history filr
 *
 * @sdata: ptr to shell inf struct
 *
 * Return: 1 if successful, 0 if not
 */
int preserve_hist(shell_info_t *sdata)
{
	ssize_t filed;
	char *filenm = retrieve_history_file(sdata);
	list_item_t *nod = NULL;

	if (!filenm)
		return (-1);
	filrd = open(filenm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenm);
	if (filed == -1)
		return (-1);
	for (nod = sdata->cmd_history; nod; nod = node->next)
	{
		_putsfd(nod->value, filed);
		_putsfd('\n', filed);
	}
	_putsfd(FLUSH_BUFFER, filed);
	close(filed);
	return (1);
}
/**
 * scan_hist - reads hist from a file
 *
 * @sdata: ptr to shell info struct
 *
 * Return: the num of entries in hist
 */
int scan_hist(shell_info_t *sdata)
{
	int u, linec = 0;
	ssize_t filed, readlen, files = 0;
	struct start st;
	char *buff = NULL, *filenm = retrieve_hist(sdata);

	if (!filenm)
		return (0);
	filed = open(filenm, O_RDONLY);
	free(filenm);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		files = st.st_size;
	if (files < 2)
		return (0);
	buff = malloc(sizeof(char) * (files + 1));
	if (!buff)
		return (0);
	readlen = read(filed, buff, files);
	buff[files] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(filed);
	for (u = 0; u < files; u++)
		if (buff[u] == '\n')
		{
			buff[u] = 0;
			add_to_history(sdata, buff + last, linc++);
			last = u + 1;
		}
	if (last != u)
		add_to_history(sdata, buff + last, linec++);
	free(buff);
	sdata->history_count = linec;
	while (sdata->history_count-- >= MAXIMUM_HISTORY_ENTERIES)
		remove_node_at_index(&(sdata->cmd_hist), 0);
	update_history_num(sdata);
	return (sdata->history_count);
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
int add_to_history(shell_info_t *sdata, char *buff, int linec)
{
	list_item_t *nod = NULL;

	if (sdata->cmd_history)
		nod = sdata->cmd_history;
	add_node_end(&nod, buff, linec);
	if (!sdata->cmd_history)
		sdata->cmd_history = nod;
	return (0);
}
/**
 * update_history_num - remmebers the history linked list after chgs
 *
 * @sdata: ptr to shell info struct
 *
 * Return: returns new hist count
 */
int update_history_num(shell_info_t *sdata)
{
	list_item_t *nod = sdata->cmd_history;
	int u = 0;

	while (nod)
	{
		node->number = u++;
		nod = node->next;
	}
	return (sdata->history_count = u)
}
