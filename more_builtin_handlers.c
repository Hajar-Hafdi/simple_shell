#include "simpleshell.h"
#include <string.h>
#include <stdio.h>

/**
 * display_history - displaays the cmd his list with line nums
 *
 * @shell_info: structure having potential args
 *
 * Return: Always 0 (Success)
 */
int display_history(shell_info_t *shell_info)
{
	if (!shell_info || !shell_info->cmd_history)
		return (1);
	output_list(shell_info->cmd_history);
	return (0);
}
/**
 * erase_alias - removes an alias
 *
 * @shell_info: structure having potential args
 * @alias_string: alias str to be removed
 *
 * Return: Always 0 if successful, 1 otherwise
 */
int erase_alias(shell_info_t *shell_info, char *alias_string)
{
	char *alias_pos, alias_char;
	int outcome;

	alias_pos = strchr(alias_string, '=');
	if (!alias_pos)
		return (1);
	alias_char = *alias_pos;
	*alias_pos = '\0';
	outcome = remove_nd_idx(&(shell_info->aliases),
			aqu_nd_indx(shell_info->aliases,
				nd_begin_with(shell_info->aliases, alias_string, -1)));
	*alias_pos = alias_char;
	return (outcome);
}
/**
 * allot_alias - sets an alias to a string
 *
 * @shell_info: structure having potential args
 * @alias_string: the alias string to be set
 *
 * Return: always 0 if successful, 1 otherwise
 */
int allot_alias(shell_info_t *shell_info, char *alias_string)
{
	char *alias_p;

	alias_p = strchr(alias_string, '=');
	if (!alias_p)
		return (1);
	if (!*++alias_p)
		return (allot_alias(shell_info, alias_string));
	return (app_ndend(&(shell_info->aliases), alias_string, 0) == NULL);
}
/**
 * output_alias - prints an alias string
 *
 * @alias_n: alias node to be printed
 *
 * Return: Always 0 if successful 1 otherwise
 */
int output_alias(list_item_t *alias_n)
{
	char *alias_p = NULL, *alias_string = NULL;

	if (alias_n)
	{
		alias_p = strchr(alias_n->value, '=');
		for (alias_string = alias_n->value; alias_string <= alias_p; alias_string++)
			putchar(*alias_string);
		putchar('\'');
		puts(alias_p + 1);
		puts("\n");
		return (0);
	}
	return (1);
}
/**
 * sshell_alias - hanles alias cmmds
 *
 * @shell_info: structure having potential args
 *
 * Return: always 0 (Success)
 */
int sshell_alias(shell_info_t *shell_info)
{
	int u = 0;
	char *alias_p = NULL;
	list_item_t *alias_n = NULL;

	if (shell_info->arg_count == 1)
	{
		alias_n = shell_info->aliases;
		while (alias_n)
		{
			output_alias(alias_n);
			alias_n = alias_n->next;
		}
		return (0);
	}
	for (u = 1; shell_info->args[u]; u++)
	{
		alias_p = strchr(shell_info->args[u], '=');
		if (alias_p)
			allot_alias(shell_info, shell_info->args[u]);
		else
			output_alias(nd_begin_with(shell_info->aliases,
						shell_info->args[u], '='));
	}
	return (0);
}
