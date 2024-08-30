#include "simpleshell.h"

/**
 * simshell_exit - exits the simple shell
 *
 * @shell_info: structure has potential args
 *
 * Return: 0 if shell_inf->arg[0] != "exit"
 */
int simshell_exit(shell_info_t *shell_info)
{
	int exit_stcheck;

	if (shell_info->args[1])
	{
		exit_stcheck = err_atoi(shell_info->args[1]);
		if (exit_stcheck == -1)
		{
			shell_info->last_status = 2;
			output_error(shell_info, "Unauthorized number: ");
			error_puts(shell_info->args[1]);
			error_putchar('\n');
			return (1);
		}
		shell_info->exit_code = exit_stcheck;
		return (-2);
	}
	shell_info->exit_code = -1;
	return (-2);
}
/**
 * shell_curdir - changes the current dir of the process
 *
 * @shell_info: structure have potential args
 *
 * Return: Always 0 (Success)
 */
int shell_curdir(shell_info_t *shell_info)
{
	char *curr_dir, *new_dir, buffer[1024];
	int chdir_ret;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		_puts("Error directory not found\n");
	if (!shell_info->args[1])
		new_dir = get_envval(shell_info, "HOME=");
	if (!new_dir)
		chdir_ret = chdir((new_dir = get_envval(shell_info, "PWD="))
				? new_dir : "/");
	else
		chdir_ret = chdir(new_dir);
	else if (_str_cmp(shell_info->args[1], "-") == 0)
		if (!get_envval(shell_info, "OLDPWD="))
			_puts(curr_dir);
	_put_char('\n');
	return (1);
	_puts(get_envval(shell_info, "OLDPWD=")), _put_char('\n');
	chdir_ret = chdir((new_dir = get_envval(shell_info, "OLDPWD="))
			? new_dir : "/");
		else
			chdir_ret = chdir(shell_info->args[1]);
	if (chdir_ret == -1)
		output_error(shell_info, "Error: couldn't change directory to: ");
	error_puts(shell_info->args[1]), error_putchar('\n');
	else
		assign_env(shell_info, "OLDPWD", get_envval(shell_info, "PWD="));
	assign_env(shell_info, "PWD", getcwd(buffer, 1024));
	return (0);
}

/**
 * simshell_help - provides help info
 *
 * @shell_info: structing having potential args
 *
 * Return: Always 0 (Success)
 */
int simshell_help(shell_info_t *shell_info)
{
	char **arg_vt;

	arg_vt = shell_info->args;
	_puts("Functionality undergoing work,Thank you for checking back later\n");
	if (0)
		_puts(*arg_vt);
	return (0);
}
