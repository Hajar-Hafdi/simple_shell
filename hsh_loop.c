#include "simpleshell.h"

/**
 * hsh - Main loop for the shell program
 * @shell_info: Structure containing shell parameters and return information
 * @argv: Array of arguments from the main function
 *
 * Return: 0 on success, 1 on error, or a specific error code
 */

int hsh(shellinfo_t *shell_info, char **argv)
{
	ssize_t res = 0;
	int built_in_r = 0;

	while (res != -1 && built_in_r != -2)
	{
		clr_shedata(shell_info);
		if (is_interactive(shell_info))
			_puts("$ ");
		error_putchar(FLUSH_BUFFER);
		res = _getinpu(shell_info);
		if (res != -1)
		{
			config_data(shell_info, argv);
			built_in_r = find_built_in(shell_info);
			if (built_in_r == -1)
				find_command(shell_info);
		}
		else if (is_interactive(shell_info))
			_put_char('\n');
		release_shdata(shell_info, 0);
	}
	preserve_hist(shell_info);
	release_shdata(shell_info, 1);
	if (!is_interactive(shell_info) && shell_info->last_status)
		exit(shell_info->last_status);
	if (built_in_r == -2)
	{
		if (shell_info->errexit_code == -1)
			exit(shell_info->last_status);
		exit(shell_info->errexit_code);
	}
	return (built_in_r);
}


/**
 * find_built_in - Searches for and executes a builtin command
 * @shell_info: Structure holding parameters and return information
 *
 * Return: -1 if builtin is not found,
 *          0 if builtin executes successfully,
 *          1 if execution fails,
 *          -2 if builtin triggers an exit signal
 */
int find_built_in(shellinfo_t *shell_info)
{
	int k, built_in_r = -1;
	builtin_table btintbl[] = {
		{"exit", simshell_exit},
		{"env", output_envir},
		{"help", simshell_help},
		{"history", display_history},
		{"setenv", set_enviro_var},
		{"unsetenv", remove_env_var},
		{"cd", shell_curdir},
		{"alias", sshell_alias},
		{NULL, NULL}
	};

	for (k = 0; btintbl[k].command; k++)
	{
		if (_str_cmp(shell_info->args[0], btintbl[k].command) == 0)
		{
			shell_info->execline_count++;
			built_in_r = btintbl[k].func(shell_info);
			break;
		}
	}
	return (built_in_r);
}

/**
 * find_command - Locates a command in the system's PATH
 * @shell_info: Structure containing parameters and return information
 *
 * Return: void
 */

void find_command(shellinfo_t *shell_info)
{
	char *c_path = NULL;
	int a, b;

	shell_info->current_path = shell_info->args[0];
	if (shell_info->count_input == 1)
	{
		shell_info->exec_count++;
		shell_info->count_input = 0;
	}
	for (a = 0, b = 0; shell_info->input[a]; a++)
		if (!is_delimeter(shell_info->input[a], " \t\n"))
			b++;
	if (!b)
		return;

	c_path = search_path(shell_info, get_envval(shell_info, "PATH="),
		shell_info->args[0]);
	if (c_path)
	{
		shell_info->current_path = c_path;
		fork_command(shell_info);
	}
	else
	{
		if ((is_interactive(shell_info) || get_envval(shell_info, "PATH=")
			|| shell_info->args[0][0] == '/')
			 && is_executable(shell_info, shell_info->args[0]))
			fork_command(shell_info);
		else if (*(shell_info->input) != '\n')
		{
			shell_info->last_status = 127;
			output_error(shell_info, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(shellinfo_t *shell_info)
{
	pid_t pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{

		perror("Error:");
		return;
	}
	if (pid_child == 0)
	{
		if (execve(shell_info->current_path, shell_info->args,
			fetch_env(shell_info)) == -1)
		{
			release_shdata(shell_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(shell_info->last_status));
		if (WIFEXITED(shell_info->last_status))
		{
			shell_info->last_status = WEXITSTATUS(shell_info->last_status);
			if (shell_info->last_status == 126)
				output_error(shell_info, "Permission denied\n");
		}
	}
}
