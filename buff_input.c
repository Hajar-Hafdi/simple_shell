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
ssize_t buff_input(shellinfo_t *sdata, char **buff, size_t *bulen)
{
	ssize_t rd = 0;
	size_t le = 0;

	if (!*bulen)
	{
		free(*buff);
		*buff = NULL;
	signal(SIGINT, sigint);
#if USE_SYSTEM_GETLINE
	rd = sh_gline(buff, &le stdin);
#else
	rd = sh_gline(sdata, buff, &le);
#endif
	if (rd > 0)
	{
		if ((*buff)[rd - 1] == '\n')
		{
			(*buff)[rd - 1] = '\0';
			rd--;
		}
		sdata->countflag_input = 1;
		remove_comm(*buff);
		add_to_history(sdata, *buff, sdata->history_count++);
		{
			*bulen = rd;
			sdata->buffer = buff;
		}
	}
	}
	return (rd);
}
