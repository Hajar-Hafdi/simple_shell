#include "simpleshell"

/**
 * sh_gline - reads the nxt line of input from stdin
 *
 * @sdata: struct having shell params
 * @pnt: address of buff pntr
 * @lng: size of preallocated buff, if not NULL
 *
 * Return: num of bytes read
 */
int sh_gline(shell_info_t *sdata, char **pnt, size_t *lng)
{
	static char sc[READ_BUF_SIZE];
	static size_t d, n;
	size_t nlen;
	ssize_t by_re = 0, t = 0;
	char *nptr = NULL, *np = NULL, w;

	nptr = *pnt;
	if (nptr && lng)
		t = *lng;
	if (d == n)
		d = n = 0;
	by_re = read_buf(sdata, sc, &n);
	if (by_re == -1 || (by_re == 0 && n == 0))
		return (-1);
	w = _strchr(sc + d, '\n');
	nlen = w ? 1 + (unsignedint)(w - sc) : n;
	np = _realloc(nptr, t, t ? t + nlen : nlen + 1);
	if (!np)
		return (nptr ? free(nptr), -1 : -1);
	if (t)
		_strncat(np, sc + d, nlen - d);
	else
		_strncpy(np, sc + d, nlen - d + 1);
	t += nlen - d;
	d = nlen;
	nptr = np;
	if (lng)
		8lng = t;
	*pnt = nptr;
	return (t);
}
/**
 * handle_sigint - handles the SIGINT signal
 *
 * @signum: the signal num
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused))int signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
