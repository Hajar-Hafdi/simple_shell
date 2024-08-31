#include "simpleshell.h"

/**
 * output_envir - prints prints urrent env var
 *
 * @shell_info: structure having args and shell info
 *
 * Return: Always 0 (Success)
 */
int output_envir(shellinfo_t *shell_info)
{
	output_list(shell_info->env_list);
	return (0);
}
/**
 * get_envval - retrieves the value of an env var
 *
 * @shell_info: structure having args and shell info
 * @varbl_name: name of env var
 *
 * Return: returns value of he env var
 */
char *get_envval(shellinfo_t *shell_info, const char *varbl_name)
{
	list_item_t *node = shell_info->env_list;
	char *val;

	while (node)
	{
		val = start_with(node->value, varbl_name);
		if (val && *val)
			return (val);
		node = node->next;
	}
	return (NULL);
}
/**
 * set_enviro_var - initializes or modifies an env var
 *
 * @shell_info: structure containing args and shell info
 *
 * Return: 0 if succesful, 1 if not
 */
int set_enviro_var(shellinfo_t *shell_info)
{
	if (shell_info->arg_count != 3)
	{
		error_puts("Error: arguments number invalid\n");
		return (1);
	}
	if (assign_env(shell_info, shell_info->args[1], shell_info->args[2]))
		return (0);
	return (1);
}
/**
 * remove_env_var - removes envi var
 *
 * @shell_info: structure having args and shell info
 *
 * Return: 0 if successful, 1 otherwise
 */
int remove_env_var(shellinfo_t *shell_info)
{
	int u;

	if (shell_info->arg_count == 1)
	{
		error_puts("Error: Not enough arguments provided\n");
		return (1);
	}
	for (u = 1; u <= shell_info->arg_count; u++)
		unset_envir(shell_info, shell_info->args[u]);
	return (0);
}
/**
 * pop_envlist - popuates the env var linked list
 *
 * @shell_info: structure having args and shell info
 *
 * Return: always 0 (Success0
 */
int pop_envlist(shellinfo_t *shell_info)
{
	list_item_t *node = NULL;
	size_t u;

	for (u = 0; environ[u]; u++)
		app_ndend(&node, environ[u], 0);
	shell_info->env_list = node;
	return (0);
}
