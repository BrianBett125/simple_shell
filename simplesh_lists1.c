#include "shell.h"

/**
 * _listleng - a function that determines length of linked list
 * @z: pointer to first node
 *
 * Return: size of list
 */
size_t _listleng(const list_tx *z)
{
	size_t f = 0;

	while (z)
	{
		z = z->next;
		f++;
	}
	return (f);
}

/**
 * **return_arrstrings - function that returns an array of strings of
 * the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **return_arrstrings(list_tx *head)
{
	list_tx *node = head;
	size_t f = list_len(head), k;
	char **strz;
	char *string;

	if (!head || !f)
		return (NULL);
	strz = malloc(sizeof(char *) * (f + 1));
	if (!strz)
		return (NULL);
	for (f = 0; node; node = node->next, f++)
	{
		string = malloc(_strlen(node->string) + 1);
		if (!string)
		{
			for (k = 0; k < f; k++)
				free(strz[k]);
			free(strz);
			return (NULL);
		}

		string = _strcpy(string, node->string);
		strz[f] = string;
	}
	strz[f] = NULL;
	return (strz);
}

/**
 * printthelist - a function that prints all elements of a list_tx linked list
 * @z: pointer to first node
 *
 * Return: size of list
 */
size_t printthelist(const list_tx *z)
{
	size_t f = 0;

	while (z)
	{
		_puts(_convertnum(z->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(z->str ? z->str : "(nil)");
		_puts("\n");
		z = z->next;
		f++;
	}
	return (f);
}

/**
 * *nodethatbegins_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefixer: string to match
 * @q: the next character after prefix to match
 *
 * Return: match node or null
 */
list_tx *nodethatbegins_with(list_tx *node, char *prefixer, char q)
{
	char *m = NULL;

	while (node)
	{
		m = starts_with(node->str, prefixer);
		if (m && ((q == -1) || (*m == q)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gets_the_nodeindex - function that will get the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
size_t gets_the_nodeindex(list_tx *head, list_tx *node)
{
	size_t f = 0;

	while (head)
	{
		if (head == node)
			return (f);
		head = head->next;
		f++;
	}
	return (-1);
}
