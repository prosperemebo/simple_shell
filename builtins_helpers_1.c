#include "main.h"

/**
 * builtin_exit - exit of the program with the status
 * @data: Program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exit(program_data *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{ /*if exists arg for exit, check if is a number*/
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9') && data->tokens[1][i] != '+')
			{ /*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: Program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_cd(program_data *data)
{
	char *dir_home = get_env_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = get_env_key("OLDPWD", data);
			if (dir_old)
				error_code = builtin_set_dir(data, dir_old);
			_print(get_env_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (builtin_set_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (builtin_set_dir(data, dir_home));
	}
	return (0);
}

/**
 * builtin_set_dir - Set working directory
 * @data: Program's data
 * @new_dir: Input path
 *
 * Return: 0 on success
 */
int builtin_set_dir(program_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_env_key("PWD", new_dir, data);
	}
	set_env_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - Shows env hints
 * @data: Program's data
 *
 * Return: 0 on success
 */
int builtin_help(program_data *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[i], length))
		{
			_print(mensajes[i] + length + 1);
			return (1);
		}
	}

	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - Show, add or remove aliases
 * @data: Program's data
 *
 * Return: 0 on success
 */
int builtin_alias(program_data *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
