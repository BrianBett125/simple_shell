#include "shell.h"
/**
 * my_strchr - finds the first appearance of a char
 * @str: string being searched
 * @c: character being searched
 * Return: nothing
 */
char *my_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}
/**
 * my_strncpy - copies a specified number of char from, one str to another
 * @strdest: string destination
 * @src: string count
 * @n: number of character
 * Return: string destination
 */
char *my_strncpy(char *strdest, const char *src, size_t n)
{
	size_t a;

	for (a = 0; a < n && src[a] != '\0'; a++)
	{
		strdest[a] = src[a];
	}
	for (; a < n; a++)
	{
		strdest[a] = '\0';
	}
	return (strdest);
}
/**
 * my_strcmp - compares strings
 * @str1: string one
 * @str2: string two
 * Return: void
 */
int my_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}
/**
 * my_realloc - dynamically changes the size of previous memory
 * @ptr: pointer
 * @new_size: new memory size
 * Return: new pointer
 */
void *my_realloc(void *ptr, unsigned int new_size)
{
	void *new_ptr = realloc(ptr, new_size);

	if (new_ptr == NULL && new_size != 0)
	{
		perror("Error: Memory allocation failed");
		return (NULL);

	}
	return (new_ptr);
}
/**
 * my_printf - works same like printf
 * @format: dictates how arguments should be formated and printed
 * Return: nothing
 */
void my_printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

