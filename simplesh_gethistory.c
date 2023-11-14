#include "shell.h"

/**
 * *recieve_historyfile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *recieve_historyfile(info_tx *info)
{
	char *buff, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, directory);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_historyfile - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_historyfile(info_tx *info)
{
	ssize_t ft;
	char *file_name = get_history_file(info);
	list_tx *node = NULL;

	if (!file_name)
		return (-1);

	ft = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (ft == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsft(node->str, ft);
		_putft('\n', ft);
	}
	_putft(BUF_FLUSH, ft);
	close(ft);
	return (1);
}

/**
 * func_readhistory - function that reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int func_readhistory(info_tx *info)
{
	int x, last = 0, ln_count = 0;
	ssize_t ft, rd_len, fl_size = 0;
	struct stat st;
	char *buff = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	ft = open(file_name, O_RDONLY);
	free(file_name);
	if (ft == -1)
		return (0);
	if (!fstat(ft, &st))
		fl_size = st.st_size;
	if (fl_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (fl_size + 1));
	if (!buff)
		return (0);
	rd_len = read(ft, buff, fl_size);
	buff[fl_size] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(ft);
	for (x = 0; x < fl_size; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			build_history_list(info, buff + last, ln_count++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(info, buff + last, ln_count++);
	free(buff);
	info->histcount = ln_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * create_historylist - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */
int create_historylist(info_tx *info, char *buffer, int line_count)
{
	list_tx *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * regivesnumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int regivesnumber_history(info_tx *info)
{
	list_tx *node = info->history;
	int e = 0;

	while (node)
	{
		node->num = e++;
		node = node->next;
	}
	return (info->histcount = e);
}
