#include "simpleshell.h"

/**
 * fetch_env - parses the string array copy of env
 *
 * @shell_data: structure having args
 *
 * Return: always 0 (Success)
 */
int **fetch_env(shell_info_t *shell_data)
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
int unset_envir(shell_info_t *shell_data, char *envi_var)
{
	list_t *nod = shell_data->env;
	size_t indx = 0;
	char *begin;

	if (!nod || !envi_var)
		return (0);
	while (nod)
	{
		begin = start_with(nod->value, envi_var);
		if (begin && *begin == '=')
		{
			shell_data->env_modified = remove_nd_idx(
					&(shell_data->env_list), indx);
			indx = 0;
			nod = shell_data->env;
			continue;
		}
		nod = nod->next;
		indx++;
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
int assign_env(shell_info_t *shell_data, char *envi_vari, char *env_val)
{
	char *buff = NULL;
	list_t *nod;
	char *begin;

	if (!envi_vari || !env_val)
		return (0);

	buff = malloc(_str_length(envi_vari) + _str_length(env_val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, envi_vari);
	_strcat(buff, "=");
	_strcat(buff, value);
	nod = shell_data->env;
	while (nod)
	{
		begin = start_with(nod->value, envi_vari);
		if (begin && *begin == "=")
		{
			free(nod->str);
			nod->str = buff;
			shell_data->env_modified = 1;
			return (0);
		}
		nod = node->next;
	}
	app_ndend(&(shell_data->env_list), buff, 0);
	free(buff);
	shell_data->env_modified = 1;
	return (0);
}
