#include "shell.h"

/**
 * hsh - main loop
 * @info:return info struct
 * @av: argument vector
 * Return: 0 or 1 or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_retturn = 0;

	while (r != -1 && builtin_retturn != -2)
	{
		clear_info(info);
		if (intrctiv(info))
			_puts("$ ");
		_eputchar(BUFF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_retturn = find_builtin(info);
			if (builtin_retturn == -1)
				find_cmd(info);
		}
		else if (intrctiv(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!intrctiv(info) && info->status)
		exit(info->status);
	if (builtin_retturn == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_retturn);
}
/**
 * find_builtin - looks for builtin commands
 * @info: returns info struct
 * Return: -1, 0, 1, or -2
 */
int find_builtin(info_t *info)
{
	int i;
	int built_in_retturn = -1;
	builtin_table builtinbl[] = {
		{"env", _myenv},
		{"exit", myexit},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", myunsetenv},
		{"cd", mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtinbl[i].type; i++)
		if (_strcmp(info->argv[0], builtinbl[i].type) == 0)
		{
			info->line_count++;
			built_in_retturn = builtinbl[i].func(info);
			break;
		}
	return (built_in_retturn);
}


/**
 * find_cmd - checks for a command in PATH
 * @info: return info struct
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i;
	int a;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, a = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], "\t\n"))
			a++;
	if (!a)
		return;

	path = find_path(info, _getenv(info, "PATH=") , info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((intrctiv(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}

		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "couldn't be found");
		}
	}
}

/**
 * fork_cmd - forks an executable to run cmd
 * @info: returns struct info
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error detected: ");
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
	}
		else
		{
			wait(&(info->status));
			if (WIFEXITED(info->status))
			{
				info->status = WEXITSTATUS(info->status);
				if (info->status == 126)
					print_error(info, "Permission was denied\n");
			}
		}
}
