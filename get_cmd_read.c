#include "simpleshell.h"

/**
 * _getinpu - gets a ine of input minus the neln
 *
 * @sdata: struct holding shell params
 *
 * Return: num of by read
 */
ssize_t _getinpu(shellinfo_t *sdata)
{
	static char *bff;
	static size_t u, k, lng;
	ssize_t b = 0;
	char *pr;

	_put_char(FLUSH_BUFFER);
	b = buff_input(sdata, &bff, &lng);
	if (b == -1)
		return (-1);
	if (lng)
	{
		k = u;
		pr = bff + u;
		chk_cmd_chain(sdata, bff, &k, u, lng);
		while (k < lng)
		{
			if (cmd_chain(sdata, bff, &k))
				break;
			k++;
		}
		u = k + 1;
		if (u >= lng)
		{
			u = lng = 0;
			sdata->buffer_type = CHAIN_NORMAL;
		}
		sdata->args = &pr;
		return (_str_length(pr));
	}
	sdata->args = &bff;
	return (b);
}
/**
 * r_bufff - reads data into a buff
 *
 * @sdata: strct holding shell params
 * @screen: screen to store the read data
 * @sze:size of screen
 *
 * Return: num of bytes read
 */
ssize_t r_bufff(shellinfo_t *sdata, char *screen, size_t *sze)
{
	ssize_t bt_r = 0;

	if (*sze)
		return (0);
	bt_r = read(sdata->input_fd, screen, READ_BUFFER_SIZE);
	if (bt_r >= 0)
		*sze = bt_r;
	return (bt_r);
}
