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
 * struct cmd_executer - Command
 * Excuter Struture
 * @cmd: Input command
 * @exe_func: Function
 */
typedef struct cmd_executer
{
	char *cmd;
	int (*exe_func)(int, char **, char *,
			program_aliases *, int *, char **, char *);
} cmd_executer;

/* line_helpers.c */
int split_line(char *, char *, program_aliases *, int *);

/* string_helpers_1.c */
char *_strpbrk(char *, char *);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
void del(char **);

/* string_helpers_2.c */
size_t _strlen(char *);
int _strcmp(const char *, char *);
int _strncmp(const char *, char *, int);
char *_strstr(char *, char *);
char *_memcpy(char *, char *, unsigned int);

/* string_helpers_3.c */
char **_strtok(char *, char *);
void swap_substring(char *, char *, char *);
int _atoi(char *);

/* getline.c */
int _getline(char **);
int _read(char **, char **);

/* executer.c */
int executer(char **, char *, char *);

/* memory_helpers.c */
void _free(char **);
void *_calloc(unsigned int, unsigned int);

/* fork.c */
int _fork(char *, char **);

/* cmd_selector.c */
int args_count(char **);
int cmd_selector(const char *, char **, char *,
		 program_aliases *, int *, char **, char *);

/* is_valid.c */
char *is_valid(char *, char *, char **);

/* env_helpers.c */
char *_getenv(char *);
int _getalias(program_aliases *, char *, int);

/* echo.c */
int echo(char **);

/* error.c */
int error(char *, char **, char *, int);

/* print_helpers.c */
int to_string(int, unsigned int);
int print_string(int, char *);

/* cmd_helpers.c */
int exit_function(int, char **, char *, program_aliases *, int *, char **, char *);
int change_dir(int, char **, char *, program_aliases *, int *, char **, char *);
int export(int, char **, char *, program_aliases *, int *, char **, char *);
int unset(int, char **, char *, program_aliases *, int *, char **, char *);
int env(int, char **, char *, program_aliases *, int *, char **, char *);

/* alias.c */
int _alias(int, char **, char *, program_aliases *, int *, char **, char *);

#endif
