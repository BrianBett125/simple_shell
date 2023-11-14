#include "shell.h"

/**
 * _my_program_exit - function that exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _my_program_exit(info_tx *info)
{
	int exit_prog;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_prog = _erratoi(info->argv[1]);
		if (exit_prog == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _my_changedir - function that changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_changedir(info_tx *info)
{
	char *string, *directory, buffer[1024];
	int chdir_return;

	string = getcwd(buffer, 1024);
	if (!string)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			chdir_return = /* TODO: what should this be? */
				chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			chdir_return = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(string);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_return = /* TODO: what should this be? */
			chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * changes - function that changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int changes(info_tx *info)
{
	char **argument_array;

	argument_array = info->argv;
	_puts("help call works. Function is not yet implemented \n");
	if (0)
		_puts(*argument_array); /* temp attt_unused workaround */
	return (0);
}
