#include "shell.h"

/**
 * is_cmd - command
 * @info: struct
 * @path: file
 *
 * Return: int 
 */
int is_cmd(info_t *info, char *path)
{
	struct stat sta;

	(void)info;
	if (!path || stat(path, &sta))
		return (0);

	if (sta.sta_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - dupl
 * @pathstr: PATHs
 * @start: starting
 * @stop: stopping
 *
 * Return: char
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int x = 0, j = 0;

	for (j = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buffer[j++] = pathstr[x];
	buffer[j] = 0;
	return (buffer);
}

/**
 * find_path - finding 
 * @info: info struct
 * @pathstr: PATHing 
 * @cmd: cmd
 *
 * Return: char
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cur = 0;
	char *pa;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			pa = dup_chars(pathstr, cur, i);
			if (!*pa)
				_strcat(pa, cmd);
			else
			{
				_strcat(pa, "/");
				_strcat(pa, cmd);
			}
			if (is_cmd(info, pa))
				return (pa);
			if (!pathstr[i])
				break;
			cur = i;
		}
		i++;
	}
	return (NULL);
}
