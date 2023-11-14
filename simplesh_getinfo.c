#include "shell.h"

/**
 * init_info - function that initializes info_tx struct
 * @info: struct address
 */
void init_info(info_tx *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setclear_info - it initializes info_tx struct
 * @info: struct address
 * @av: argument vector
 * Return: nothing
 */
void setclear_info(info_tx *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info_struct - function which frees info_tx struct fields
 * @info: struct address
 * @yes: true if freeing all fields
 */
void free_info_struct(info_tx *info, int yes)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (yes)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
