#include "main.h"

/**
 * expand_variables - expands environment variables and other special variables in the input line
 */
// void expand_variables(program_data *data)
// {
// 	expand_line(data);
// }

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(program_data *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	append_string(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			append_string(expansion, line + i + j);
			line[i] = '\0';
			append_string(line, temp);
			line[str_length(line)] = '\0';
			append_string(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * append_string - Adds input string to end of buffer
 * @buffer: Input buffer
 * @str: Input string
 *
 * Return: int
 */
int append_string(char *buffer, char *str)
{
	int length, i;

	length = str_length(buffer);
	for (i = 0; str[i]; i++)
	{
		buffer[length + i] = str[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
