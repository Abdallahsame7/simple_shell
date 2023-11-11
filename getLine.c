#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the len variable.
 *
 * Return: Number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rrr = 0;
	size_t len_ppp = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rrr = getline(buf, &len_ppp, stdin);
#else
		rrr = _getline(info, buf, &len_ppp);
#endif
		if (rrr > 0)
		{
			if ((*buf)[rrr - 1] == '\n')
			{
				(*buf)[rrr - 1] = '\0'; /* remove trailing newline */
				rrr--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = rrr;
				info->cmd_buf = buf;
			}
		}
	}
	return (rrr);
}

/**
 * get_input - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *bufff; /* the ';' command chain buffer */
	static size_t iii, jjj, lennn;
	ssize_t rrr = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rrr = input_buf(info, &buf, &lennn);
	if (rrr == -1) /* EOF */
		return (-1);
	if (lennn)	/* we have commands left in the chain buffer */
	{
		jjj = iii; /* init new iterator to current buf position */
		p = buf + iii; /* get pointer for return */

		check_chain(info, buf, &jjj, iii, lennn);
		while (jjj < lennn) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			jjj++;
		}

		iii = jjj + 1; /* increment past nulled ';'' */
		if (iii >= lennn) /* reached end of buffer? */
		{
			iii = lennn = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (rrr); /* return length of buffer from _getline() */
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: The result of the read operation.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rrr = 0;

	if (*i)
		return (0);
	rrr = read(info->readfd, buf, READ_BUF_SIZE);
	if (rrr >= 0)
		*i = rrr;
	return (rrr);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The result of the read operation.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t iii, lennn;
	size_t kkk;
	ssize_t rrr = 0, sss = 0;
	char *ppp = NULL, *new_ppp = NULL, *ccc;

	ppp = *ptr;
	if (ppp && length)
		sss = *length;
	if (iii == lennn)
		iii = lennn = 0;

	rrr = read_buf(info, buf, &lennn);
	if (rrr == -1 || (rrr == 0 && lennn == 0))
		return (-1);

	ccc = _strchr(buf + i, '\n');
	kkk = ccc ? 1 + (unsigned int)(ccc - buf) : lennn;
	new_ppp = _realloc(ppp, sss, sss ? sss + kkk : kkk + 1);
	if (!new_ppp) /* MALLOC FAILURE! */
		return (ppp ? free(ppp), -1 : -1);

	if (sss)
		_strncat(new_ppp, buf + iii, kkk - iii);
	else
		_strncpy(new_ppp, buf + iii, kkk - iii + 1);

	sss += kkk - iii;
	iii = kkk;
	ppp = new_ppp;

	if (length)
		*length = sss;
	*ptr = ppp;
	return (sss);
}

/**
 * sigintHandler - Blocks the Ctrl-C signal.
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
