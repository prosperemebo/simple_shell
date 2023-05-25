#include "main.h"

/**
 * expand_variables - Expands variables in the input line.
 * @data: Pointer to program data.
 *
 * This function expands special variables ('$?' and '$$') as well as
 * environment variables ('$<variable>') in the input line. It modifies
 * the input line in-place.
 */
void expand_variables(program_data *data)
{
	char line[BUFFER_SIZE] = {0};

	if (!data->input_line)
		return;

	append_string(line, data->input_line);

	expand_special_variables(data, line);
	expand_environment_variables(data, line);

	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_special_variables - Expands special variables in the given line.
 * @data: Pointer to program data.
 * @line: Line to expand variables in.
 *
 * This function expands special variables ('$?' and '$$') in the given line.
 * It modifies the line in-place.
 */
void expand_special_variables(program_data *data, char *line)
{
	int i;
	char expansion[BUFFER_SIZE] = {0};

	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			append_string(line, expansion);
			append_string(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			append_string(line, expansion);
			append_string(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
	}
}

/**
 * expand_environment_variables - Expands environment variables
 * in the given line.
 * @data: Pointer to program data.
 * @line: Line to expand variables in.
 *
 * This function expands environment
 * variables ('$<variable>') in the given line.
 * It modifies the line in-place.
 */
void expand_environment_variables(program_data *data, char *line)
{
	int i, j, expand_len;
	char expansion[BUFFER_SIZE] = {0};
	char *temp, *ptr;

	for (i = 0; line[i]; i++)
	{
		if (line[i] == '$')
		{
			ptr = expansion;
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				ptr[j - 1] = line[i + j];
			ptr[j - 1] = '\0';
			temp = get_env_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			expand_len = j + 1 + (temp ? str_length(temp) : 0);
			ptr = malloc(sizeof(char) * expand_len);
			if (!ptr)
				exit_shell(EXIT_FAILURE, "Memory allocation error\n");
			if (temp)
				str_copy(ptr, temp, expand_len);
			else
				ptr[0] = '\0';
			append_string(ptr, line + i + j);
			append_string(line, ptr);
			free(ptr);
		}
	}
}
