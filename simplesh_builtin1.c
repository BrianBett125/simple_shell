#include "shell.h"

/**
 * _my_cmd_history - function displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_cmd_history(info_tx *info)
{
	print_list(info->history);
	return (0);
}

/**
 * rem_alias - function that sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int rem_alias(info_tx *info, char *str)
{
	char *d, c;
	int re;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	c = *d;
	*d = 0;
	re = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*d = c;
	return (re);
}

/**
 * pre_set_alias - function sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int pre_set_alias(info_tx *info, char *str)
{
	char *m;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	if (!*++m)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_string - function that prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_tx *node)
{
	char *boy = NULL, *a = NULL;

	if (node)
	{
		boy = _strchr(node->str, '=');
		for (a = node->str; a <= boy; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(boy + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mimic_alias - function that mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int mimic_alias(info_tx *info)
{
	int x = 0;
	char *y = NULL;
	list_tx *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		y = _strchr(info->argv[x], '=');
		if (y)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
