#include "shell.h"

/**
 * *the_headnode_add - function that adds a node to the start of the list
 * @head: address of pointer to head node
 * @string: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_tx *the_headnode_add(list_tx **head, const char *string, int num)
{
	list_tx *add_head;

	if (!head)
		return (NULL);
	add_head = malloc(sizeof(list_tx));
	if (!add_head)
		return (NULL);
	_memset((void *)add_head, 0, sizeof(list_tx));
	add_head->num = num;
	if (string)
	{
		add_head->string = _strdup(string);
		if (!add_head->string)
		{
			free(add_head);
			return (NULL);
		}
	}
	add_head->next = *head;
	*head = add_head;
	return (add_head);
}

/**
 * *new_end_node - function that adds a node to the end of the list
 * @head: address of pointer to head node
 * @string: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_tx *new_end_node(list_tx **head, const char *string, int num)
{
	list_tx *tail_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	tail_node = malloc(sizeof(list_tx));
	if (!tail_node)
		return (NULL);
	_memset((void *)tail_node, 0, sizeof(list_tx));
	tail_node->num = num;
	if (string)
	{
		tail_node->string = _strdup(string);
		if (!tail_node->string)
		{
			free(tail_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = tail_node;
	}
	else
		*head = tail_node;
	return (tail_node);
}

/**
 * _printliststr - prints only the str element of a list_tx linked list
 * @u: pointer to first node
 *
 * Return: size of list
 */
size_t _printliststr(const list_tx *u)
{
	size_t t = 0;

	while (u)
	{
		_puts(u->str ? u->str : "(nil)");
		_puts("\n");
		u = u->next;
		i++;
	}
	return (t);
}

/**
 * deletethe_node_atindex - function which deletes node at given index
 * @head: address of pointer to first node
 * @indexed: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deletethe_node_atindex(list_tx **head, unsigned int indexed)
{
	list_tx *node, *previous_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!indexed)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == indexed)
		{
			previous_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freedlist - function that frees all nodes of a list
 * @headptr: address of pointer to head node
 *
 * Return: void
 */
void _freedlist(list_tx **headptr)
{
	list_tx *node, *following_node, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		following_node = node->next;
		free(node->str);
		free(node);
		node = following_node;
	}
	*headptr = NULL;
}
