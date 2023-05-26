#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

extern char **environ;
extern int EXIT_STATUS;

/**
 * struct aliases - Struct aliases
 * @name: alias name
 * @value: alias value
 */
typedef struct program_aliases
{
	char *name;
	char *value;
} program_aliases;

/**
 * struct cmd_executer - structure
 * @cmd: command
 * @exe_func: function
 */
typedef struct cmd_executer
{
	char *cmd;
	int (*exe_func)(int, char **, char *,
			program_aliases *, int *, char **, char *);
} cmd_executer;

/* line_helpers.c */
void check_alias(char ***arr, program_aliases *alias, int idx);
int and_handling(char *line, char *name, program_aliases *alias, int *idx);
int or_handling(char *line, char *name, program_aliases *alias, int *idx);
int semi_column_handling(char *line, char *name, program_aliases *alias, int *idx);
int split_line(char *line, char *name, program_aliases *alias, int *idx);

/*int split_line(char *, char *, program_aliases *, int *); */
char **_strtok(char *, char *);
int _getline(char **);
int _read(char **, char **);
void check_fork_error(char *, char **, char *);
int executer(char **, char *, char *);
void get_cmds(char ***, char *);
void _free(char **);
void *_calloc(unsigned int, unsigned int);
int _fork(char *, char **);
int args_count(char **);
char *is_valid(char *, char *, char **);
int args_count(char **);
char *check_ops(char **);
char *_getenv(char *);
int _getalias(program_aliases *, char *, int);
int echo(char **);
int error(char *, char **, char *, int);

/* printing functions */
int to_string(int, unsigned int);
int print_string(int, char *);
/* for cmd exec */

int cmd_selector(const char *, char **, char *,
		 program_aliases *, int *, char **, char *);
int change_dir(int, char **, char *, program_aliases *, int *, char **, char *);
int exit_function(int, char **, char *, program_aliases *, int *, char **, char *);
int export(int, char **, char *, program_aliases *, int *, char **, char *);
int unset(int, char **, char *, program_aliases *, int *, char **, char *);
int env(int, char **, char *, program_aliases *, int *, char **, char *);
int _alias(int, char **, char *, program_aliases *, int *, char **, char *);

/* custom string functions */
char **_strtok(char *, char *);
char *_strpbrk(char *, char *);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
void del(char **);
size_t _strlen(char *);
int _strcmp(const char *, char *);
int _strncmp(const char *, char *, int);
char *_strstr(char *, char *);
char *_memcpy(char *, char *, unsigned int);
void replace_substring(char *, char *, char *);
int _atoi(char *);

#endif
