#include "simpleshell.h"

/**
 * get_cmd - gets a ine of input minus the neln
 *
 * @sdata: struct holding shell params
 *
 * Return: num of by read
 */
ssize_t get_cmd(shell_info_t *sdata)
{
	static char *bff;
	static size_t u, k, lng;
	ssize_t bread = 0;
	char **arg_p = &(sdata->args), *pntr;

	_putchar(FLUSH_BUFFER);
	bread = buff_input(sdata, &bff, &lng);
	if (bread == -1)
		return (-1);
	if (lng)
	{
		k = u;
		pntr = bff + u;
		handle_cmd_chain(sdata, bff, &k, u, lng);
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
		*arg_p = pntr;
		return (_str_length(pntr));
	}
	*arg_p = bff;
	return (bread);
}
/**
 * read_bf - reads data into a buff
 *
 * @sdata: strct holding shell params
 * @screen: screen to store the read data
 * @sze:size of screen
 *
 * Return: num of bytes read
 */
ssize_t read_bf(shell_info_t *sdata, char *screen, size_t *sze)
{
	ssize_t bt_r = 0;

	if (*sze)
		return (0);
	bt_r = read(sdata->input_fd, screen, READ_BUF_SIZE);
	if (bt_r >= 0)
		*sze = bt_r;
	return (bt_r);
}
