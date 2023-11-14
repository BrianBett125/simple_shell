#include "shell.h"

/**
 * **getmy_environ - function that returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getmy_environ(info_tx *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * mv_setenv - function that Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int mv_setenv(info_tx *info, char *var)
{
	list_tx *node = info->env;
	size_t j = 0;
	char *pr;

	if (!node || !var)
		return (0);

	while (node)
	{
		pr = starts_with(node->str, var);
		if (pr && *pr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _set_newenv - function that Initializes a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env variable property
 * @va_lue: the string environment var value
 *  Return: Always 0
 */
int _set_newenv(info_tx *info, char *var, char *va_lue)
{
	char *buff = NULL;
	list_tx *node;
	char *pr;

	if (!var || !va_lue)
		return (0);

	buf = malloc(_strlen(var) + _strlen(va_lue) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, va_lue);
	node = info->env;
	while (node)
	{
		pr = starts_with(node->str, var);
		if (pr && *pr == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
