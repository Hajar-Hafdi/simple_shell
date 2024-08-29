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
		exit_stchack = _erratoi(shell_info->args[1]);
		if (exit_stcheck == -1)
		{
			shell_info->exit_code = 2;
			print_error(shell_info, "Illegal number: ");
			_eputs(shell_info->args[1]);
			_eputchar('\n');
			return (1);
		}
		shell_info->err_num = _erratoi(shell_info->args[1]);
		return (-2);
	}
	shell_info->err_num = -1;
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
	int change_dir;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		_puts("Error: couldn't find directory\n");
	if (!shell_info->args[1])
		new_dir = _gentenv(shell_info, "HOME=");
		if (!new_dir)
		change_dir = chdir((new_dir = _getenv(shell_info, "PWD="))
					? new_dir : "/");
		else
			change_dir = chdir(new_dir);
	else if (_strcmp(shell_info->args[1], "-") == 0)
	if (!_getenv(shell_info, "OLDPWD="))
		_puts(curr_dir);
	_putchar('\n');
	return (1);
	_puts(_getenv(shell_info, "OLDPWD=")), _putchar('\n');
	change_dir = chdir((new_dir = _getenv(shell_info, "OLDPWD")) ? new_dir : "/");
	else
		change_dir = chdir(shell_info->args[1]);
	if (change_dir == -1)
		print_error(shell_info, "unable to change directory to ");
	_eputs(shell_info->args[1]), _eputchar('\n');
	else
		_setenv(shell_info, "OLDPWD", _getenv(shell_info, "PWD="));
	_setenv(shell_info, "PWD", getcwd(buffer 1024));
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
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_vt);
	return (0);
}
