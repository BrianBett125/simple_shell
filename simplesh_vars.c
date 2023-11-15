#include "shell.h"

/**
 * funct_ischain - function to test if current char in buffer is a
 * chain delimeter
 * @info: the parameter struct
 * @buff: the charactor buffer
 * @z: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int funct_ischain(info_tx *info, char *buff, size_t *z)
{
	size_t f = *z;

	if (buff[f] == '|' && buff[f + 1] == '|')
	{
		buff[f] = 0;
		f++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[f] == '&' && buff[f + 1] == '&')
	{
		buff[f] = 0;
		f++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[f] == ';') /* found end of this command */
	{
		buff[f] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*z = f;
	return (1);
}

/**
 * checkifcontinue_chain - function to check if we should continue
 * chaining based on last status
 *
 * @info: the parameter struct
 * @buff: the char buffer
 * @z: address of current position in buff
 * @a: starting position in buff
 * @lenz: length of buffer
 *
 * Return: Void
 */
void checkifcontinue_chain(info_tx *info, char *buff, size_t *z,
		size_t a, size_t lenz)
{
	size_t f = *z;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[a] = 0;
			f = lenz;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[a] = 0;
			f = lenz;
		}
	}

	*z = f;
}

/**
 * replac_etoken_alias - function that replaces an aliases in the
 * tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replac_etoken_alias(info_tx *info)
{
	int x;
	list_tx *node;

	char *q

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * change_vars - function replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_vars(info_tx *info)
{
	int x = 0;
	list_tx *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			change_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			change_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			change_string(&(info->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * change_string - function that replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
