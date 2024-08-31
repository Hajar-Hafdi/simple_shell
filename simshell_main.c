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
	shellinfo_t shell_info = INFO_INIT;
	int input_file_desc;

	if (arg_cnt == 2)
	{
		input_file_desc = open(arg_val[1], O_RDONLY);
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
		shell_info.input_fd = input_file_desc;
	}
	pop_envlist(&shell_info);
	scan_hist(&shell_info);
	hsh(&shell_info, arg_val);
	return (EXIT_SUCCESS);
    /* Close the file descriptor if it's not the standard input*/
	if (input_file_desc != STDIN_FILENO)
	close(input_file_desc);

    return (EXIT_SUCCESS);
}
