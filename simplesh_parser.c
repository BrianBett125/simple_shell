#include "shell.h"

/**
 * check_execmd - function that determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_execmd(info_tx *info, char *path)
{
	struct stat sr;

	(void)info;
	if (!path || stat(path, &sr))
		return (0);

	if (sr.sr_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * *func_dupchars - function thatduplicates characters
 * @pathstring: the PATH string
 * @start: starting index
 * @halt: stopping index
 *
 * Return: pointer to new buffer
 */
char *func_dupchars(char *pathstring, int start, int halt)
{
	static char buf[1024];
	int d = 0, y = 0;

	for (y = 0, d = start; d < halt; d++)
		if (pathstring[d] != ':')
			buf[y++] = pathstring[d];
	buf[y] = 0;
	return (buf);
}

/**
 * *locate_path - finds this command in the PATH string
 * @info: the info struct
 * @pathstring: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *locate_path(info_tx *info, char *pathstring, char *cmd)
{
	int p = 0, current_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstring[p] || pathstring[p] == ':')
		{
			path = dup_chars(pathstring, current_pos, p);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstring[p])
				break;
			current_pos = p;
		}
		p++;
	}
	return (NULL);
}
