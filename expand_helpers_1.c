#include "main.h"

/**
 * expand_variables - Expand shell variables
 * @data: Pointer to program_data struct
 */
void expand_variables(program_data *data)
{
	int i, j, expand_len;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {0};
	char *temp, *ptr;

	if (!data->input_line)
		return;

	append_string(line, data->input_line);

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
		else if (line[i] == '$')
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

	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_error - expands the $? variable to the last error code
 */
/*
void expand_error(char *line)
{
	char *pos = strstr(line, "$?");

	if (pos != NULL)
	{
		char expansion[BUFFER_SIZE];
		long_to_string(errno, expansion, 10);
		append_string(line, expansion);
		append_string(line, pos + 2);
	}
} */

/**
 * expand_pid - expands the $$ variable to the current process ID
 */
/*
void expand_pid(char *line)
{
	char *pos = strstr(line, "$$");

	if (pos != NULL)
	{
		char expansion[BUFFER_SIZE];
		long_to_string(getpid(), expansion, 10);
		append_string(line, expansion);
		append_string(line, pos + 2);
	}
} */

/**
 * expand_env - expands environment variables (e.g. $PATH)
 */
/*
void expand_env(char *line, program_data *data)
{
	char *pos = strstr(line, "$");

	while (pos != NULL)
	{
		char *end = pos + 1;

		while (*end != ' ' && *end != '\0')
			end++;

		char key[BUFFER_SIZE];
		str_copy(key, pos + 1, end - pos - 1);
		char *value = get_env_key(key, data);

		if (value != NULL)
		{
			append_string(line, value);
			append_string(line, end);
		}
		else
		{
			append_string(line, pos);
		}

		pos = strstr(end, "$");
	}
} */

/**
 * expand_line - expands the entire command line
 */
/*
void expand_line(program_data *data)
{
	char line[BUFFER_SIZE];
	append_string(line, data->input_line);

	// Remove comments
	char *pos = strstr(line, "#");
	if (pos != NULL)
		*pos = '\0';

	// Expand variables
	expand_error(line);
	expand_pid(line);
	expand_env(line, data);

	// Update input line
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
*/
