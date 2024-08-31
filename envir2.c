#include "simpleshell.h"

/**
 * fetch_env - parses the string array copy of env
 *
 * @shell_data: structure having args
 *
 * Return: always 0 (Success)
 */
char **fetch_env(shellinfo_t *shell_data)
{
	if (!shell_data->env_array || shell_data->env_modified)
	{
		shell_data->env_array = lst_str(shell_data->env_list);
		shell_data->env_modified = 0;
	}
	return (shell_data->env_array);
}
/**
 * unset_envir - remove an env var
 *
 * @shell_data: structure having pot args
 * @envi_var: the string env variable prop
 *
 * Return: 1 if deleted, 0 otherwise
 */
int unset_envir(shellinfo_t *shell_data, char *envi_var)
{
	list_item_t *node = shell_data->env_list;
	size_t in = 0;
	char *b;

	if (!node || !envi_var)
		return (0);
	while (node)
	{
		b = start_with(node->value, envi_var);
		if (b && *b == '=')
		{
			shell_data->env_modified = remove_nd_idx(
					&(shell_data->env_list), in);
			in = 0;
			node = shell_data->env_list;
			continue;
		}
		node = node->next;
		in++;
	}
	return (shell_data->env_modified);
}
/**
 * assign_env - initialize an env var
 *
 * @shell_data: structure having pot args
 * @envi_vari: the string env var
 * @env_val: the string env var val
 *
 * Return: always 0 (Success)
 */
int assign_env(shellinfo_t *shell_data, char *envi_vari, char *env_val)
{
	char *buff = NULL;
	list_item_t *node;
	char *b;

	if (!envi_vari || !env_val)
		return (0);

	buff = malloc(_str_length(envi_vari) + _str_length(env_val) + 2);
	if (!buff)
		return (1);
	_str_copy(buff, envi_vari);
	_str_cat(buff, "=");
	_str_cat(buff, env_val);

	node = shell_data->env_list;
	while (node)
	{
		b = start_with(node->value, envi_vari);
		if (b && *b == '=')
		{
			free(node->value);
			node->value = buff;
			shell_data->env_modified = 1;
			return (0);
		}
		node = node->next;
	}
	app_ndend(&(shell_data->env_list), buff, 0);
	free(buff);
	shell_data->env_modified = 1;
	return (0);
}
