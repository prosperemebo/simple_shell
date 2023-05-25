#include "main.h"

/**
 * get_env_key - Get enviroment variable value
 * @key: Enviroment variable
 * @data: struct of the program's data
 *
 * Return: Pointer to enviroment variable or NULL
 */
char *get_env_key(char *key, program_data *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		    data->env[i][key_length] == '=')
		{
			return (data->env[i] + key_length + 1);
		}
	}

	return (NULL);
}

/**
 * set_env_key - Create or overwrite enviroment variable
 * @key: Enviroment variable
 * @value: Input value
 * @data: struct of the program's data
 *
 * Return: INT
 */

int set_env_key(char *key, char *value, program_data *data)
{
	int i, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		    data->env[i][key_length] == '=')
		{
			is_new_key = 0;

			free(data->env[i]);
			break;
		}
	}

	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{

		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * remove_env_key - Remove enviroment variable
 * @key: Input key
 * @data: the sructure of the program's data
 *
 * Return: INT
 */
int remove_env_key(char *key, program_data *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		    data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}

			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_enviroment - Print current enviroment
 * @data: Program's data
 *
 * Return: NULL
 */
void print_enviroment(program_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
