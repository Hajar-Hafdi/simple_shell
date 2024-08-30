#include "simpleshell.h"

/**
 * main - entry point for the sinple shell prog
 *
 * @arg_cnt: args count
 * @arg_val: vector of arg
 *
 * Return: 0 if succesful, 1 otherwise
 */
int main(int arg_cnt, char **arg_val)
{
	shell_info_t shell_info = INFO_INIT;
	int input_file_desc;

	if (arg_cnt == 2)
	{
		input_file_desc = open(arg_val[1], 0_RDONLY);
		if (input_file_desc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_puts(arg_val[0]);
				error_puts("wasn't able to open");
				error_puts(arg_val[1]);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_info.input_fd = input_file_descriptor;
	}
	pop_envlist(&shell_info);
	retrieve_hist(&shell_info);
	hsh(&shell_info, arg_val);
	return (EXIT_SUCCESS);
}
