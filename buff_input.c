#include "simpleshell.h"

/**
 * buff_input - buffers c cmd
 *
 * @sdata: ptr to shell info struct
 * @buff: address of buff ptr
 * @bulen: addrss of buff len var
 *
 * Return: num of bytes read
 */
ssize_t buff_input(shell_info_t *sdata, char **buff, size_t *bulen)
{
	ssize_t by_read = 0;
	size_t lentm = 0;

	if (!bulen)
		return -1;
	*buff = NULL;
	signal(SIGINT, handle_sigint);
#if USE_SYSTEM_GETLINE
	by_read = getline(buff, &lentm, stdin);
#else
	by_read = sh_gline(sdata, buff, &lentm);
#endif
	if (by_read > 0)
	{
		if ((*buff)[by_read - 1] == '\n')
		{
			(*buff)[by_read - 1] = '\0';
			by_read--;
		}
		sdata->count_input = 1;
		remove_comm(*buff);
		add_to_history(sdata, *buff, sdata->history_count++);
		*bulen = by_read;
		sdata->buffer = buff;
	}
	return (by_read);
}
