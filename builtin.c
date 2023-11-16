#include "shell.h"

/**
 * myexit - exits shell
 * @info: maintains constant fuction prototype
 * Return: (0) with a given condition
 *		info.argv[0] != "exit"
 */
int myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);


	if (exitcheck == -1)
	{
		info->status = 2;
		print_error(info, "incorrect number: ");
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
 * mycd - changes directory
 * @info: used to maintain function prototype
 * Return: (0)
 */
int mycd(info_t *info)
{
	char *s;
	char buffer[1024];
	char *dir;
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<< \n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
	if (!dir)
		chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
	else
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);

}

/**
 * _myhelp - changes direct of the process
 * @info: argument structure
 * Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_arry;

	arg_arry = info->argv;
	_puts("Help works, function not yet implemented\n");

	if (0)
		_puts(*arg_arry);
	return (0);
}
