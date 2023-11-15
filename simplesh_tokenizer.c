#include "shell.h"

/**
 * **string_to_words - function that splits a string into words. Repeat
 * delimiters are ignored
 *
 * @strn: the input string
 * @w: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_to_words(char *strn, char *w)
{
	int i, r, k, m, numofwords = 0;
	char **q;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	if (!w)
		w = " ";
	for (i = 0; strn[i] != '\0'; i++)
		if (!is_delim(strn[i], w) && (is_delim(strn[i + 1], w) || !strn[i + 1]))
			numofwords++;

	if (numofwords == 0)
		return (NULL);
	q = malloc((1 + numofwords) * sizeof(char *));
	if (!q)
		return (NULL);
	for (i = 0, r = 0; r < numofwords; r++)
	{
		while (is_delim(strn[i], w))
			i++;
		k = 0;
		while (!is_delim(strn[i + k], w) && strn[i + k])
			k++;
		q[r] = malloc((k + 1) * sizeof(char));
		if (!q[r])
		{
			for (k = 0; k < r; k++)
				free(q[k]);
			free(q);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			q[r][m] = strn[i++];
		q[r][m] = 0;
	}
	q[r] = NULL;
	return (q);
}

/**
 * **funcstring_tow2 - splits a string into words
 * @strn: the input string
 * @w: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **funcstring_tow2(char *strn, char w)
{
	int i, r, k, m, numofwords = 0;
	char **q;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	for (i = 0; strn[i] != '\0'; i++)
		if ((strn[i] != w && strn[i + 1] == w) ||
		    (strn[i] != w && !strn[i + 1]) || strn[i + 1] == w)
			numofwords++;
	if (numofwords == 0)
		return (NULL);
	q = malloc((1 + numofwords) * sizeof(char *));
	if (!q)
		return (NULL);
	for (i = 0, r = 0; r < numofwords; r++)
	{
		while (strn[i] == w && strn[i] != w)
			i++;
		k = 0;
		while (strn[i + k] != w && strn[i + k] && strn[i + k] != w)
			k++;
		q[r] = malloc((k + 1) * sizeof(char));
		if (!q[r])
		{
			for (k = 0; k < r; k++)
				free(q[k]);
			free(q);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			q[r][m] = strn[i++];
		q[r][m] = 0;
	}
	q[r] = NULL;
	return (q);
}
