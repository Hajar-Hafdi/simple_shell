#include "simpleshell.h"

/**
 * clr_shedata - initializes shellinfo_t strct
 *
 * @sdata: ptr to the shellinfo_t struct
 */
void clr_shedata(shellinfo_t *sdata)
{
	sdata->input = NULL;
	sdata->args = NULL;
	sdata->current_path = NULL;
	sdata->arg_count = 0;
}
/**
 * config_data - sets up the shellinfo_t struct
 *
 * @sdata: ptr to the shellinfo_t strct
 * @argvec: arg vector
 */
void config_data(shellinfo_t *sdata, char **argvec)
{
	int u = 0;

	sdata->program_name = argvec[0];
	if (sdata->input)
	{
		sdata->args = split_string(sdata->input, " \t");
		if (!sdata->args)
		{
			sdata->args = malloc(sizeof(char *) * 2);
			if (sdata->args)
			{
				sdata->args[0] = _strd_up(sdata->input);
				sdata->args[1] = NULL;
			}
		}
		for (u = 0; sdata->args && sdata->args[u]; u++)
			;
		sdata->arg_count = u;
		change_aliases(sdata);
		change_vars(sdata);
	}
}
/**
 * release_shdata - releases memory for fields in shellinfo_t strct
 *
 * @shell_info: ptr to the shellinfo_t struct
 * @freeall: flag thet indicates whether to free all fields
 */
void release_shdata(shellinfo_t *shell_info, int freeall)
{
	f_free(shell_info->args);
	shell_info->args = NULL;
	shell_info->current_path = NULL;

	if (freeall)
	{
		if (!shell_info->buffer)
			free(shell_info->input);
		if (shell_info->env_list)
			libre_list(&(shell_info->env_list));
		if (shell_info->cmd_history)
			libre_list(&(shell_info->cmd_history));
		if (shell_info->aliases)
			libre_list(&(shell_info->aliases));
		f_free(shell_info->env_array);
		shell_info->env_array = NULL;
		b_free((void **)shell_info->buffer);
		if (shell_info->input_fd > 2)
			close(shell_info->input_fd);
		_put_char(FLUSH_BUFFER);
	}
}
