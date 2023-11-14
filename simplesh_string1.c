#include "shell.h"

/**
 * *func_string_cpy - fuction that copies a string
 * @destin: the destination
 * @srcs: the source
 *
 * Return: pointer to destination
 */
char *func_string_cpy(char *destin, char *srcs)
{
	int t = 0;

	if (destin == srcs || srcs == 0)
		return (destin);
	while (srcs[t])
	{
		destin[t] = srcs[t];
		t++;
	}
	destin[t] = 0;
	return (destin);
}

/**
 * *funcstringdup - function that duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *funcstringdup(const char *string)
{
	int length = 0;
	char *rets;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	rets = malloc(sizeof(char) * (length + 1));
	if (!rest)
		return (NULL);
	for (length++; length--;)
		rets[length] = *--string;
	return (rets);
}

/**
 *_funcinputs - function that prints an input string
 *@strn: the string to be printed
 *
 * Return: Nothing
 */
void _funcinputs(char *strn)
{
	int d = 0;

	if (!strn)
		return;
	while (strn[d] != '\0')
	{
		_putchar(strn[d]);
		d++;
	}
}

/**
 * _writeputchar - function that writes the character z to stdout
 * @z: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writeputchar(char z)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (z == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(1, buf, p);
		p = 0;
	}
	if (z != BUF_FLUSH)
		buf[p++] = z;
	return (1);
}
