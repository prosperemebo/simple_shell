#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include "macros.h"

/**
 * struct program_data - Program's data
 * @program_name: Name of program executable
 * @input_line: Pointer to input for _getline
 * @command_name: Pointer to first input command
 * @exec_counter: Number of comands executed
 * @file_descriptor: File descriptor to the input of commands
 * @tokens: Pointer to array of tokenized input
 * @env: Enviroment
 * @alias_list: Array of pointers aliases
 */
typedef struct program_data
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} program_data;

/**
 * struct built_ins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct built_ins
{
	char *built_in;
	int (*function)(program_data *data);
} built_ins;

/* print_helpers.c */
int _print(char *string);
int _printe(char *string);
int _print_error(int errorcode, program_data *data);

/* shell.c */
void prepare_program(program_data *data, int arc, char *argv[], char **env);
void prompt_manager(char *prompt, program_data *data);
void quit_shell(int opr UNUSED);
int execute(program_data *data);

/* _getline.c */
int _getline(program_data *data);
int check_operators(char *array_commands[], int i, char array_operators[]);

/* expand_helpers_1.c */
void expand_variables(program_data *data);
void expand_special_variables(program_data *data, char *line);
void expand_environment_variables(program_data *data, char *line);

/* expand_helpers_2.c */
void expand_alias(program_data *data);
int append_string(char *buffer, char *str);

/* string_helpers_1.c */
int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_copy(char *ptr, char *temp, int expand_len);

/* string_helpers_2.c */
void str_reverse(char *string);
void tokenise_string(program_data *data);
char *_strtok(char *line, char *delim);

/* number_helpers.c */
void long_to_string(long number, char *string, int base);
int count_characters(char *string, char *character);
int _atoi(char *s);

/* path_helpers.c */
char **tokenise_path(program_data *data);
int get_program(program_data *data);
int check_file(char *full_path);

/* memory_helpers.c */
void free_array_of_pointers(char **directories);
void free_duplicate_data(program_data *data);
void free_all_data(program_data *data);
void exit_shell(int exit_code, char *message);

/* env_helpers.c */
char *get_env_key(char *name, program_data *data);
int set_env_key(char *key, char *value, program_data *data);
int remove_env_key(char *key, program_data *data);
void print_enviroment(program_data *data);

/* alias_helpers.c */
int print_alias(program_data *data, char *alias);
char *get_alias(program_data *data, char *alias);
int set_alias(char *alias_string, program_data *data);

/* builtin_helpers_1.c */
int builtin_exit(program_data *data);
int builtin_cd(program_data *data);
int builtin_set_dir(program_data *data, char *new_dir);
int builtin_help(program_data *data);
int builtin_alias(program_data *data);

/* builtin_helpers_2.c */
int builtins_list(program_data *data);
int builtin_env(program_data *data);
int builtin_set_env(program_data *data);

#endif
