#include "simpleshell.h"

/**
 * sh_gline - reads the nxt line of input from stdin
 *
 * @sdata: struct having shell params
 * @pnt: address of buff pntr
 * @lng: size of preallocated buff, if not NULL
 *
 * Return: num of bytes read
 */
int sh_gline(shellinfo_t *sdata, char **pnt, size_t *lng)
{
	static char sc[READ_BUFFER_SIZE];
	static size_t d, n;
	size_t nlen;
	ssize_t by_re = 0, t = 0;
	char *nptr = NULL, *np = NULL, *w;

	nptr = *pnt;
	if (nptr && lng)
		t = *lng;
	if (d == n)
		d = n = 0;
	by_re = r_bufff(sdata, sc, &n);
	if (by_re == -1 || (by_re == 0 && n == 0))
		return (-1);
	w = _str_chr(sc + d, '\n');
	nlen = w ? 1 + (unsigned int)(w - sc) : n;
	np = realloc(nptr, t ? t + nlen : nlen + 1);
	if (!np)
		return (nptr ? free(nptr), -1 : -1);
	if (t)
		_strn_cat(np, sc + d, nlen - d);
	else
		_strn_cpy(np, sc + d, nlen - d + 1);
	t += nlen - d;
	d = nlen;
	nptr = np;
	if (lng)
		*lng = t;
	*pnt = nptr;
	return (t);
}
/**
 * sigint - handles the SIGINT signal
 *
 * @dt: the signal num
 *
 * Return: void
 */
void sigint(__attribute__((unused))int dt)
{
	_puts("\n");
	_puts("$ ");
	_put_char(FLUSH_BUFFER);
}
