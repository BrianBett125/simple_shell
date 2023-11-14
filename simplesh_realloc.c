#include "shell.h"

/**
 * *_memoryfill - function that fills memory with a constant byte
 * @v: the pointer to the memory area
 * @b: the byte to fill *v with
 * @x: the amount of bytes to be filled
 * Return: (v) a pointer to the memory area v
 */
char *_memoryfill(char *v, char b, unsigned int x)
{
	unsigned int t;

	for (t = 0; t < x; t++)
		v[t] = b;
	return (v);
}

/**
 * _f_free - function that frees a string of strings
 * @yy: string of strings
 */
void _f_free(char **yy)
{
	char **r = yy;

	if (!yy)
		return;
	while (*yy)
		free(*yy++);
	free(r);
}

/**
 * *func_realloc - function that reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @oldsize: byte size of previous block
 * @newsize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *func_realloc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
	char *g;

	if (!ptr)
		return (malloc(newsize));
	if (!newsize)
		return (free(ptr), NULL);
	if (newsize == oldsize)
		return (ptr);

	g = malloc(newsize);
	if (!g)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		g[oldsize] = ((char *)ptr)[oldsize];
	free(ptr);
	return (g);
}
