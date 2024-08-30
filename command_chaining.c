#include "simpleshell.h"

/**
 * cmd_chain - checks if current char is a chain del
 *
 * @shell_info: param structure
 * @buff: char buffer
 * @pos: address of curr pos in buff
 *
 * Return: 1 if chain del, 1 if not
 */
int cmd_chain(shell_info_t *shell_info, char *buff, size_t *pos)
{
	size_t indx = *pos;

	if (buff[indx] == '|' && buff[indx + 1] == '|')
	{
		buff[indx] = '\0';
		indx++;
		shell_info->buffer_type = CHAIN_OR;
	}
	else if (buff[indx] == ';')
	{
		buff[indx] = '\0';
		shell_info->buffer_type = CHAIN_NORMAL;
	}
	else
		return (0);
	*pos = indx;
	return (1);
}
/**
 * handle_cmd_chain - handles coms chaining based on the last status
 *
 * @inf: ptr to shell information structure
 * @buff: char buff
 * @indx: address of the curr pos in buff
 * @strt: starting pos in buff
 * @buf_l: length of the buffer
 *
 * Return: void
 */
void handle_cmd_chain(shell_info_t *inf, char *buff, size_t *indx,
		size_t strt, size_t buf_l)
{
	size_t pos = *indx;

	if (inf->buffer_type == CHAIN_AND)
	{
		if (inf->last_status)
		{
			buff[strt] = '\0';
			pos = buf_l;
		}
	}
	else if (info->buffer_type == CHAIN_OR)
	{
		if (!inf->last_status)
		{
			buff[strt] = '\0';
			pos = buf_l;
		}
	}
	*indx = pos;
}
/**
 * change_aliases - replaces aliases in the tokenized string
 *
 * @inf: ptr to the shell info structure
 *
 * Return: 1 if succesfully replaced, 0 if not
 */
int change_aliases(shell_info_t *inf)
{
	int u;
	list_item_t *nod;
	char *equals_s;

	for (u = 0; u < 10; u++)
	{
		nod = nd_begin_with(inf->aliases, inf->args[0], '=');
		if (!nod)
			return (0);
		free(inf->args[0]);
		equals_s = strchr(nod->value, '=');
		if (!equals_s)
			return (0);
		equals_s = strdup(equals_s + 1);
		if (!equals_s)
			return (0);
		inf->args[0] = equals_s;
	}
	return (1);
}
/**
 * change_vars - replaces vars in tokenize str
 *
 * @inf: ptr to shell information structure
 *
 * Return: 1 if succesfully change, 0 if not
 */
int change_vars(shell_info_t *inf)
{
	int u = 0;
	list_item_t *nod;

	for (u = 0; inf->args[u]; u++)
	{
		if (inf->args[u][0] != '$' || !inf->args[u][1])
			continue;
		if (!strcmp(inf->args[u], "$?"))
		{
			replace_string(&(inf->args[u]),
					_strd_up(convert_num(inf->exit_code, 10, 0)));
			continue;
		}
		if (!strcmp(inf->args[u], "$$"))
		{
			replace_string(&(inf->args[u]),
					_strd_up(conver_num(getpid(), 10, 0)));
			continue;
		}
		nod = find_node_with_prefix(inf->env_list, &inf->args[u][1], '=');
		if (nod)
		{
			replace_string(&(inf->args[u]),
					_strd_up(strchr(nod->value, '=') + 1));
			continue;
		}
		replace_string(&inf->args[u], strdup(""));
	}
	return (0);
}
/**
 * replace_string - replaces a string with a nw one
 *
 * @prev_str: address of the previous string
 * @curr_str: address of the current string
 *
 * Return: 1 if succesfully replaced, 0 otherwise
 */
int replace_string(char **prev_str, char *curr_str)
{
	free(*prev_str);
	*prev_str = curr_str;
	return (1);
}
