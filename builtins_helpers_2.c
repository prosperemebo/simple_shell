#include "main.h"

/**
 * builtins_list - Matches executable builtin
 * @data: Program's data
 *
 * Return: Match or -1
 **/
int builtins_list(program_data *data)
{
	int i;
	built_ins options[] = {
	    {"exit", builtin_exit},
	    {"help", builtin_help},
	    {"cd", builtin_cd},
	    {"alias", builtin_alias},
	    {"env", builtin_env},
	    {"setenv", builtin_set_env},
	    {"unsetenv", builtin_unset_env},
	    {NULL, NULL}};

	for (i = 0; options[i].built_in != NULL; i++)
	{

		if (str_compare(options[i].built_in, data->command_name, 0))
		{

			return (options[i].function(data));
		}
	}
	return (-1);
}

/**
 * builtin_env - Show enviroment
 * @data: Program's data
 *
 * Return: 0 on success
 */
int builtin_env(program_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		print_enviroment(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = str_duplicate(get_env_key(cpname, data));
				if (var_copy != NULL)
					set_env_key(cpname, data->tokens[1] + i + 1, data);
				print_enviroment(data);
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
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - Set enviroment variables
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
		return (5);
	}

	set_env_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - Unsets enviroment variable
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
		return (5);
	}
	remove_env_key(data->tokens[1], data);

	return (0);
}
