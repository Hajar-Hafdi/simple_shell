#include "simpleshell.h"

/**
 * is_executable - checks if a file is an executable command
 * @shell_info: the info struct
 * @path: path to the file
 *
 * Return: return 1 if true, or 0 otherwise
 */
int is_executable(shell_info_t *shell_info, char *path)
{
	struct stat fl_stat;

	(void)shell_info;
	if (!path || stat(path, &fl_stat) != 0)
		return (0);

	if (fl_stat.st_mode & S_IFREG)
	{
		if (fl_stat.st_mode & S_IXUSR)
			return (1);
	}
	return (0);
}

/**
 * dup_character - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_character(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * search_path - finds this cmd in the PATH string
 * @shell_info: the info struct
 * @pathst: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *search_path(shell_info_t *shell_info, char *pathst, char *cmd)
{
	int k = 0, current_pos = 0;
	char *path;

	if (!pathst)
		return (NULL);
	if ((_str_length(cmd) > 2) && start_with(cmd, "./"))
	{
		if (is_executable(shell_info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathst[k] || pathst[k] == ':')
		{
			path = dup_character(pathst, current_pos, k);
			if (!*path)
				_str_cat(path, cmd);
			else
			{
				_str_cat(path, "/");
				_str_cat(path, cmd);
			}
			if (is_executable(shell_info, path))
				return (path);
			if (!pathst[k])
				break;
			current_pos = k;
		}
		k++;
	}
	return (NULL);
}
