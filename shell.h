#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>



/* Reading and Writing buffers */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024


/* Used to differentiate commands */
#define CMD_NORM	0
#define CMD_AND 2
#define CMD_CHAIN	3
#define CMD_OR  1

/* convert_number() */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

/* defines getline() and strtok() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* defines the name of the history file and size */
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"


extern char **environ;


/**
 * liststr - struct for strings of a singly linked list
 * @str: this is a string variable
 * @num: field num
 * @next: it points to where the next node is
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * passinfo - struct containing information for command execution
 * @err_num: code for error exits
 * @alias: node of alias
 * @argv: strings of an array
 * @line_count_flag: error number
 * @fname: filename
 * @line_count: number of errors
 * @environ: modified eviron
 * @path: string path
 * @argc: count of an argument
 * @env: environ copy
 * struct passinfo - contains arguements to pass,
 * @history: node of history
 * @arg: string created by getline
*/
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_r;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains only two functions
 * @type: flag builtin command
 * @func: a function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_r *);
} builtin_table;


/* functions for loophsh.c */
int loophsh(char **);

/* functions for toem_parser.c */
int is_cmd(info_r *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_r *, char *, char *);

/* functions for toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*functions for toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*functions for toem_shloop.c */
int hsh(info_r *, char **);
int find_builtin(info_r *);
void find_cmd(info_r *);
void fork_cmd(info_r *);

/* functions for toem_builtin1.c */
int _ishistory(info_r *);
int _isalias(info_r *);

/* functions for toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* functions for toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* functions for toem_exits.c */
char *_strncut(char *, char *, int);
char *_strchr(char *, char);
char *_strncopy(char *, char *, int);

/* functions for toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* functions for toem_memory.c */
int bfree(void **);


/* functions for toem_errors1.c */
int _erratoi(char *);
void print_error(info_r *, char *);
int print_f(int, int);
char *conv_number(long int, int, int);
void remove_comments(char *);

/*functions for toem_builtin.c */
int _isexit(info_r *);
int _iscd(info_r *);
int _ishelp(info_r *);

/* functions for toem_environ.c */
char *_getenv(info_r *, const char *);
int _isenv(info_r *);
int _issetenv(info_r *);
int _isunsetenv(info_r *);
int populate_env_list(info_r *);

/*functions for toem_getinfo.c */
void clear_info(info_r *);
void set_info(info_r *, char **);
void free_info(info_r *, int);

/*functions for toem_vars.c */
int is_chain(info_r *, char *, size_t *);
void check_chain(info_r *, char *, size_t *, size_t, size_t);
int replace_alias(info_r *);
int replace_vars(info_r *);
int replace_string(char **, char *);

/*functions for toem_getline.c */
ssize_t get_input(info_r *);
int _getline(info_r *, char **, size_t *);
void sigintHandler(int);

/* functions for toem_getenv.c */
char **get_environ(info_r *);
int _unsetenv(info_r *, char *);
int _setenv(info_r *, char *, char *);

/*functions for toem_history.c */
char *get_history_file(info_r *info);
int write_history(info_r *info);
int read_history(info_r *info);
int build_history_list(info_r *info, char *buf, int linecount);
int renumber_history(info_r *info);

/*functions for toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*functions for toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*functions for toem_atoi.c */
int interactive(info_r *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

#endif
