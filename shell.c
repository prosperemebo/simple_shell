#include "main.h"

/**
 * main - Program Init
 * @argc: Number of input values
 * @argv: Input values
 * @env: Enviroment variables
 * Return: zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
	program_data data_struct;
	program_data *data = &data_struct;

	data_struct.input_line = NULL;

	prepare_program(data, argc, argv, env);

	signal(SIGINT, quit_shell);

	prompt_manager(data);

	return 0;
}

/**
 * quit_shell - Handles user quitting the shell
 */
void quit_shell(int opr UNUSED)
{
	_print("\n");
	print_prompt();
}

/**
 * prepare_program - Prepares struct data for the program
 * @data: Pointer to data
 * @argv: Inputs
 * @argc: Number of inputs
 * @env: Environment variables
 */
void prepare_program(program_data *data, int argc, char *argv[], char **env)
{
	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;

	if (argc == 1)
	{
		data->file_descriptor = STDIN_FILENO;
	}
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			perror(data->program_name);
			exit(EXIT_FAILURE);
		}
	}

	data->tokens = NULL;
	data->env = env;
	data->alias_list = NULL;
}

/**
 * prompt_manager - Keeps the shell running
 * @data: Program's data
 */
void prompt_manager(program_data *data)
{
	int string_count = 0;

	while (++(data->exec_counter))
	{
		print_prompt();
		string_count = _getline(data);

		if (string_count == EOF)
		{
			free_all_data(data);
			exit(EXIT_SUCCESS);
		}

		if (string_count >= 1)
		{
			tokenise_string(data);
			if (data->tokens[0])
			{
				execute(data);
			}
			free_duplicate_data(data);
		}
	}
}

/**
 * execute - Execute commands
 * @data: Program's data
 */
void execute(program_data *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(data->command_name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(data->tokens[0], data->tokens, data->env);
		perror(data->command_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			errno = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			errno = 128 + WTERMSIG(status);
		}
	}
}
