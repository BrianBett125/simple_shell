#include "shell.h"

/**
 * funcname_hsh - function that is the main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int funcname_hsh(info_tx *info, char **av)
{
	ssize_t q = 0;
	int builtinretn = 0;

	while (q != -1 && builtinretn != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		q = get_input(info);
		if (q != -1)
		{
			set_info(info, av);
			builtinretn = find_builtin(info);
			if (builtinretn == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtinretn == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtinretn);
}

/**
 * locatethe_builtin - function that finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locatethe_builtin(info_tx *info)
{
	int e, _builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (e = 0; builtintbl[e].type; e++)
		if (_strcmp(info->argv[0], builtintbl[e].type) == 0)
		{
			info->line_count++;
			_builtin_ret = builtintbl[e].func(info);
			break;
		}
	return (_builtin_ret);
}

/**
 * _find_command - function that finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _find_command(info_tx *info)
{
	char *path = NULL;
	int c, v;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (c = 0, v = 0; info->arg[c]; c++)
		if (!is_delim(info->arg[c], " \t\n"))
			k++;
	if (!v)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * _fork_command - function that forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _fork_command(info_tx *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
