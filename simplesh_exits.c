#include "shell.h"

/**
 * *stringcopy - function that copies a string
 * @destination: the new location the string is to be copied to
 * @source: the source string
 * @num: the amount of characters to be copied
 * Return: the concatenated string
 */
char *stringcopy(char *destination, char *source, int num)
{
	int i, k;
	char *d = destination;

	i = 0;
	while (source[i] != '\0' && i < num - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < num)
	{
		k = i;
		while (k < num)
		{
			destination[k] = '\0';
			k++;
		}
	}
	return (d);
}

/**
 * *string_concat - function that concatenates two strings
 * @first: the first string
 * @next: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *string_concat(char *first, char *next, int n)
{
	int i, j;
	char *m = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (next[j] != '\0' && j < n)
	{
		first[i] = next[j];
		i++;
		j++;
	}
	if (j < n)
		first[i] = '\0';
	return (m);
}

/**
 * *string_find - locates a character in a string
 * @b: the string to be parsed
 * @c: the character to look for
 * Return: (b) a pointer to the memory area b
 */
char *string_find(char *b, char c)
{
	do {
		if (*b == c)
			return (b);
	} while (*b++ != '\0');

	return (NULL);
}
