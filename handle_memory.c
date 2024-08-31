#include "simpleshell.h"

/**
 **_mem_set - fills the first byte of memory with a constant byte
 *@str: pointer to the memory area
 *@byte: byte to fill *str with
 *@num: the amount of bytes to be filled
 *Return: (str) a pointer to the memory area s
 */
char *_mem_set(char *str, char byte, unsigned int num)
{
	unsigned int k;

	for (k = 0; k < num; k++)
		str[k] = byte;
	return (str);
}

/**
 * f_free - free a string of strings
 * @ptr: pointer to string of strings
 */
void f_free(char **ptr)
{
	char **s = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(s);
}

/**
 * _re_allocate - reallocates a block of memory
 * @pointer: pointer to previous malloc'ed block
 * @old_s: byte size of the previous block
 * @new_s: byte size of the new block
 *
 * Return: pointer to the new alocated block.
 */
void *_re_allocate(void *pointer, unsigned int old_s, unsigned int new_s)
{
	char *ptr;

	if (!pointer)
		return (malloc(new_s));
	if (!new_s)
		return (free(pointer), NULL);
	if (new_s == old_s)
		return (pointer);

	ptr = malloc(new_s);
	if (!ptr)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		ptr[old_s] = ((char *)pointer)[old_s];
	free(pointer);
	return (ptr);
}

/**
 * b_free - frees a pointer and set the address to NULL
 * @p: address of the pointer to be free
 *
 * Return: 1 on success, 0 otherwise.
 */
int b_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
