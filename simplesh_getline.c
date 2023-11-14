#include "shell.h"

/**
 * _input_buffer - function that buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t _input_buffer(info_tx *info, char **buff, size_t *length)
{
	ssize_t n = 0;
	size_t len_q = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buff, &len_q, stdin);
#else
		n = _getline(info, buff, &len_q);
#endif
		if (n > 0)
		{
			if ((*buff)[n - 1] == '\n')
			{
				(*buff)[n - 1] = '\0'; /* remove trailing newline */
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*length = n;
				info->cmd_buf = buff;
			}
		}
	}
	return (n);
}

/**
 * get_newlineinput - function that gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_newlineinput(info_tx *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, j, length;
	ssize_t v = 0;
	char **buff_z = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	v = input_buf(info, &buf, &length);
	if (v == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = x; /* init new iterator to current buf position */
		p = buf + x; /* get pointer for return */

		check_chain(info, buf, &j, x, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		x = j + 1; /* increment past nulled ';'' */
		if (x >= length) /* reached end of buffer? */
		{
			x = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_z = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buff_z = buf; /* else not a chain, pass back buffer from _getline() */
	return (v); /* return length of buffer from _getline() */
}

/**
 * func_readthebuff - a function thatreads a buffer
 * @info: parameter struct
 * @buffer: represents buffer
 * @s: size
 *
 * Return: r
 */
ssize_t func_readthebuff(info_tx *info, char *buffer, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(info->readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*s = r;
	return (r);
}

/**
 * getnextline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int getnextline(info_tx *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, lenz;
	size_t lk;
	ssize_t e = 0, s = 0;
	char *p = NULL, *new_d = NULL, *o;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == lenz)
		a = lenz = 0;

	e = read_buf(info, buf, &lenz);
	if (e == -1 || (e == 0 && lenz == 0))
		return (-1);

	o = _strchr(buf + a, '\n');
	lk = o ? 1 + (unsigned int)(o - buf) : lenz;
	new_d = _realloc(p, s, s ? s + lk : lk + 1);
	if (!new_d) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_d, buf + a, lk - a);
	else
		_strncpy(new_d, buf + a, lk - a + 1);

	s += lk - a;
	a = lk;
	p = new_d;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sig_nal_int_handler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void sig_nal_int_handler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
