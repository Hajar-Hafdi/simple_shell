#include "simpleshell.h"

/**
 * simshell_exit - exits the simple shell
 *
 * @shell_info: structure has potential args
 *
 * Return: 0 if shell_inf->arg[0] != "exit"
 */
int simshell_exit(shellinfo_t *shell_info)
{
	int exit_stcheck;

	if (shell_info->args[1])
	{
		exit_stcheck = error_atoi(shell_info->args[1]);
		if (exit_stcheck == -1)
		{
			shell_info->last_status = 2;
			output_error(shell_info, "Unauthorized number: ");
			error_puts(shell_info->args[1]);
			error_putchar('\n');
			return (1);
		}
		shell_info->errexit_code = error_atoi(shell_info->args[1]);
		return (-2);
	}
	shell_info->errexit_code = -1;
	return (-2);
}
/**
 * shell_curdir - changes the current dir of the process
 *
 * @shell_info: structure have potential args
 *
 * Return: Always 0 (Success)
 */
int shell_curdir(shellinfo_t *shell_info)
{
	char *o, drt, buffer[1024];
	int chdir_ret;

	o = getcwd(buffer, sizeof(buffer)1024);
	if (!o)
		_puts("Error: directory not found\n");
	if (!shell_info->args[1])
	{
		drt = _getenv(shell_info, "HOME=");
		if (!drt)
			chdir_ret = chdir((drt = _getenv(shell_info, "PWD=")) ? drt : "/");
		else
			chdir_ret = chdir(drt);
	}
	else if (_strcmp(shell_info->args[1], "-") == 0)
	{
		if (!_getenv(shell_info, "OLDPWD="))
		{
			_puts(s);
			_put_char('\n');
			return (1);
		}
		_puts(get_evval(shell_info, "OLDPWD=")), _put_char('\n');
		chdir_ret = chdir((drt = get_envval(shell_info, "OLDPWD=")) ? drt : "/");
	}
	else
		chdir_ret = chdir(shell_info->args[1]);
	if (chdir_ret == -1)
	{
		output_error(shell_info, "couldn't change dir to ");
		error_puts(shell_info->args[1]), error_putchar('\n');
	}
	else
	{
		set_enviro_var(shell_info, "OLDPWD", get_envval(shell_info, "PWD="));
		set_enviro_var(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * simshell_help - provides help info
 *
 * @shell_info: structing having potential args
 *
 * Return: Always 0 (Success)
 */
int simshell_help(shellinfo_t *shell_info)
{
	char **arg_vt;

	arg_vt = shell_info->args;
	_puts("Functionality undergoing work,Thank you for checking back later\n");
	if (0)
	{
		_puts(*arg_vt);
	}
	return (0);
}
