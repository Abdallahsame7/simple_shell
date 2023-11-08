#include "shell.h"

/**
 * _myexit - Exit the shell.
 * @info: Structure containing potential arguments.
 * 
 * Return: Exits with a given exit status (0 if info.argv[0] is "exit").
 */
int _myexit(info_t *info)
{
	int exiting;

	if (info->argv[1])  /* If there is an exit arguement */
	{
        
		exiting = _erratoi(info->argv[1]);
		if (exiting == -1)
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
 * _mycd - Change the current directory of the process.
 * @info: Structure containing potential arguments.
 * 
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *S;
    char *direct;
    char buffer[1024];
	int chdir_reting;

	S = getcwd(buffer, 1024);
	if (!S)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direct = _getenv(info, "HOME=");
		if (!direct)
			chdir_reting = /* TODO: what should this be? */
				chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			chdir_reting = chdir(direct);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(S);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_reting = /* TODO: what should this be? */
			chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
	}
	else
		chdir_reting = chdir(info->argv[1]);
	if (chdir_reting == -1)
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
 * _myhelp - Change the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * 
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	char **arg_arrayyy;

	arg_arrayyy = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arrayyy); /* temp att_unused workaround */
	return (0);
}
