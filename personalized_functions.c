#include "shell.h"
/**
 * my_strcspn - determines length of initial seg of string
 * that has characters not specified in a set.
 * @string: string being examined
 * @set: char to be matched
 * Return: len of segment
 */
size_t my_strcspn(const char *string, const char *set)
{
	size_t len = 0;
	const char *pr;

	while (*string != '\0')
	{
		pr = set;
		while (*pr != '\0')
		{
			if (*string == *pr)
			{
				return (len);
			}
			pr++;
		}
		string++;
		len++;
	}

	return (len);
}
/**
 * my_strlen - finds length of a null terminated string
 * @strcnt: string whose length is being calculated
 * Return: the length
 */
int my_strlen(const char *strcnt)
{
	int c = 0;

	while (strcnt[c])
		c++;

	return (c);
}
/**
 * my_strdup - duplicates anew copy of string
 * @str: string being duplicated
 * Return: duplicated string
 */
char *my_strdup(char *str)
{
	int index = 0, len = 1;
	char *strdup;

	if (str == NULL)
		return (NULL);

	len = my_strlen(str);
	strdup = malloc((sizeof(char) * len) + 1);
	if (strdup == NULL)
		return (NULL);

	while (index < len)
	{
		strdup[index] = str[index];
		index++;
	}

	strdup[index] = '\0';
	return (strdup);
}
