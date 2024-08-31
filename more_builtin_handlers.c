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
	char *sign, tempp;
	int outcome;

	sign = _str_chr(alias_string, '=');
	if (!sign)
		return (1);
	tempp = *sign;
	*sign = '\0';
	outcome = remove_nd_idx(&(shell_info->aliases),
			aqu_nd_indx(shell_info->aliases,
				nd_begin_with(shell_info->aliases, alias_string, -1)));
	*sign = tempp;
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
	char *signn;

	signn = _str_chr(alias_string, '=');
	if (!signn)
		return (1);
	if (!*++signn)
		 return (erase_alias(shell_info, alias_string));
	erase_alias(shell_info, alias_string);
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
	char *siign = NULL, *astring = NULL;

	if (alias_n)
	{
		siign = _str_chr(alias_n->value, '=');
		for (astring = alias_n->value; astring <= siign; astring++)
			_put_char(*astring);
		_put_char('\'');
		_puts(siign + 1);
		_puts("'\n");
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
	char *ssign = NULL;
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
		ssign = _str_chr(shell_info->args[u], '=');
		if (ssign)
			allot_alias(shell_info, shell_info->args[u]);
		else
			output_alias(nd_begin_with(shell_info->aliases,
						shell_info->args[u], '='));
	}
	return (0);
}
