#include "shell.h"

/**
 * convertoi - function that converts a string to an integer
 * @t: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int convertoi(char *t)
{
	int i = 0;
	unsigned long int result = 0;

	if (*t == '+')
		t++;  /* TODO: why does this make main return 255? */
	for (i = 0;  t[i] != '\0'; i++)
	{
		if (t[i] >= '0' && t[i] <= '9')
		{
			result *= 10;
			result += (t[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error - function that prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_error(info_tx *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * display_decimal - function that prints a decimal (integer) number of base 10
 * @input: the new caractor input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int display_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, counter = 0;
	unsigned int now, currently;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		now = -input;
		__putchar('-');
		counter++;
	}
	else
		now = input;
	currently = now;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (now / x)
		{
			__putchar('0' + current / x);
			counter++;
		}
		currently %= x;
	}
	__putchar('0' + currently);
	counter++;

	return (counter);
}

/**
 * *change_num - a converter function, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *change_num(long int number, int base, int flags)
{
	static char *arrays;
	static char buff[50];
	char signs = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		signs = '-';

	}
	arrays = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arrays[n % base];
		n /= base;
	} while (n != 0);

	if (signs)
		*--ptr = signs;
	return (ptr);
}

/**
 * delete_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void delete_comments(char *buff)
{
	int o;

	for (o = 0; buff[o] != '\0'; o++)
		if (buff[o] == '#' && (!o || buff[o - 1] == ' '))
		{
			buff[o] = '\0';
			break;
		}
}
