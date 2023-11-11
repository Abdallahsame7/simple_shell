#include "shell.h"

/**
 * get_history_file - Gets the path to the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the path to the history file.
 */
char *get_history_file(info_t *info)
{
	char *bufff, *dirrr;

	dirrr = _getenv(info, "HOME=");
	if (!dirrr)
		return (NULL);
	bufff = malloc(sizeof(char) * (_strlen(dirrr) + _strlen(HIST_FILE) + 2));
	if (!bufff)
		return (NULL);
	bufff[0] = 0;
	_strcpy(bufff, dirrr);
	_strcat(bufff, "/");
	_strcat(bufff, HIST_FILE);
	return (bufff);
}

/**
 * write_history - Creates a file or appends to an existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_t *info)
{
	ssize_t fddd;
	char *filenameee = get_history_file(info);
	list_t *nodeee = NULL;

	if (!filenameee)
		return (-1);

	fddd = open(filenameee, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenameee);
	if (fddd == -1)
		return (-1);
	for (nodeee = info->history; nodeee; nodeee = nodeee->next)
	{
		_putsfd(nodeee->str, fddd);
		_putfd('\n', fddd);
	}
	_putfd(BUF_FLUSH, fddd);
	close(fddd);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @info: The parameter struct.
 *
 * Return: The number of history entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int iii, lasttt = 0, linecounttt = 0;
	ssize_t fddd, rdlennn, fsizeee = 0;
	struct stat sttt;
	char *bufff = NULL, *filenameee = get_history_file(info);

	if (!filenameee)
		return (0);

	fddd = open(filenameee, O_RDONLY);
	free(filenameee);
	if (fddd == -1)
		return (0);
	if (!fstat(fddd, &sttt))
		fsizeee = sttt.st_size;
	if (fsizeee < 2)
		return (0);
	bufff = malloc(sizeof(char) * (fsizeee + 1));
	if (!bufff)
		return (0);
	rdlennn = read(fddd, bufff, fsizeee);
	bufff[fsizeee] = 0;
	if (rdlennn <= 0)
		return (free(bufff), 0);
	close(fddd);
	for (iii = 0; iii < fsizeee; iii++)
		if (bufff[iii] == '\n')
		{
			bufff[iii] = 0;
			build_history_list(info, bufff + lasttt, linecounttt++);
			lasttt = iii + 1;
		}
	if (lasttt != iii)
		build_history_list(info, bufff + lasttt, linecounttt++);
	free(bufff);
	info->histcount = linecounttt;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buf: Buffer.
 * @linecount: The history line count, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nodeee = NULL;

	if (info->history)
		nodeee = info->history;
	add_node_end(&nodeee, buf, linecount);

	if (!info->history)
		info->history = nodeee;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments. Used to maintain.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *nodeee = info->history;
	int iii = 0;

	while (nodeee)
	{
		nodeee->num = iii++;
		nodeee = nodeee->next;
	}
	return (info->histcount = iii);
}
