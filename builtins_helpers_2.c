#include "main.h"

/**
 * builtin_env - Show environment
 * @data: Program's data
 *
 * Return: 0 on success
 */
int builtin_env(program_data *data)
{
	if (data->tokens[1] == NULL)
		print_environment(data);
	else
		handle_env_assignment(data);

	return (0);
}

/**
 * handle_env_assignment - Handles environment variable assignment
 * @data: Program's data
 */
void handle_env_assignment(program_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	for (i = 0; data->tokens[1][i]; i++)
	{
		if (data->tokens[1][i] == '=')
		{
			var_copy = str_duplicate(get_env_key(cpname, data));
			if (var_copy != NULL)
				set_env_key(cpname, data->tokens[1] + i + 1, data);
			print_environment(data);
			if (get_env_key(cpname, data) == NULL)
			{
				_print(data->tokens[1]);
				_print("\n");
			}
			else
			{
				set_env_key(cpname, var_copy, data);
				free(var_copy);
			}
			return;
		}
		cpname[i] = data->tokens[1][i];
	}

	errno = 2;
	perror(data->command_name);
	errno = 127;
}

/**
 * builtin_set_env - Set environment variables
 * @data: Program's data
 *
 * Return: 0 on success
 */
int builtin_set_env(program_data *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);

	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return 5;
	}

	set_env_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - Unsets environment variable
 * @data: Program's data
 *
 * Return: 0 on success
 */
int builtin_unset_env(program_data *data)
{
	if (data->tokens[1] == NULL)
		return (0);

	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return 5;
	}

	remove_env_key(data->tokens[1], data);

	return (0);
}
