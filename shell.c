#include "main.h"

/**
 * main - Program Init
 * @argc: Number of input values
 * @argv: Input values
 * @env: Enviroment variables
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	program_data data_struct;
	program_data *data = &data_struct;
	char *prompt = "";

	data_struct.input_line = NULL;

	prepare_program(data, argc, argv, env);

	signal(SIGINT, quit_shell);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	prompt_manager(prompt, data);
	return (0);
}

/**
 * quit_shell - Handles user quit shell
 *
 * @UNUSED: Prototype option
 */
void quit_shell(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * prepare_program - Prepares struct data for program
 * @data: Pointer to data
 * @argv: Inputs
 * @argc: Number of inputs
 * @env: Enviroment variables
 */
void prepare_program(program_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * prompt_manager - Keeps shell running
 * @prompt: Prompt to be printed
 * @data: Programs data
 */
void prompt_manager(char *prompt, program_data *data)
{
	int error_code = 0;
	int string_count = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_count = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_count >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenise_string(data);
			if (data->tokens[0])
			{
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_duplicate_data(data);
		}
	}
}

/**
 * execute - Execute commands
 * @data: Program's data
 *
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(program_data *data)
{
	int retval = 0, status;
	pid_t pidd;

	retval = builtin_env(data);
	if (retval != -1)
		return (retval);

	retval = get_program(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
