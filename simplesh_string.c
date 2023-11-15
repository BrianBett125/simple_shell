#include "shell.h"

/**
 * _stringretlen - function that returns the length of a string
 * @g: the string whose length to check
 *
 * Return: integer length of string
 */
int _stringretlen(char *g)
{
	int v = 0;

	if (!g)
		return (0);

	while (*g++)
		v++;
	return (v);
}

/**
 * _stringcomparison - function that performs lexicogarphic comparison of
 * two strangs.
 * @Sa: the first strang
 * @Sb: the second strang
 *
 * Return: negative if Sa < Sb, positive if Sa > Sb, zero if Sa == Sb
 */
int _stringcomparison(char *Sa, char *Sb)
{
	while (*Sa && *Sb)
	{
		if (*Sa != *Sb)
			return (*Sa - *Sb);
		Sa++;
		Sb++;
	}
	if (*Sa == *Sb)
		return (0);
	else
		return (*Sa < *Sb ? -1 : 1);
}

/**
 * *funcstarts_with - functio nthat checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *funcstarts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * *func_stringcat - function that concatenates two strings
 * @destin: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *func_stringcat(char *destin, char *source)
{
	char *rets = destin;

	while (*destin)
		destin++;
	while (*source)
		*destin++ = *source++;
	*destin = *source;
	return (rets);
}
