#include "shell.h"

/**
 * inpu_str - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void inpu_str(char *str)
{
	int y = 0;

	if (!str)
		return;
	while (str[y] != '\0')
	{
		_eputchar(str[y]);
		y++;
	}
}

/**
 * write_stderr - function that writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_stderr(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * putcharfd - writes the character k to given fd
 * @k: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putcharfd(char k, int fd)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(fd, buf, b);
		b = 0;
	}
	if (k != BUF_FLUSH)
		buf[b++] = k;
	return (1);
}

/**
 * func_putsfd - function that prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int func_putsfd(char *str, int fd)
{
	int z = 0;

	if (!str)
		return (0);
	while (*str)
	{
		z += _putfd(*str++, fd);
	}
	return (z);
}
