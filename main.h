#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*for command chain*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

/* IF USING SYSTEM getline()*/
#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: string
 * @next: pointer to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_st;

/**
 * struct passinfo - contain pseudo-arguments to pass into a function
 * allowing uniform prototype function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of string
 * @path: a string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: program file name
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from ll env
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environ changed
 * @status: return status of the last executed command
 * @cmd_buf: address of pointer to cmd_buf, on if chain
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read the line input
 * @histcount: history line count
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
	list_st *env;
	list_st *history;
	list_st *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_st;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - have built in string and related functions
 * @type: the builting command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_st *);
} builtin_table;

void exe_cmd(char **argv); /*exec_cmd.c*/
void get_location(info_st *info); /*get_locat.c*/

/* string.c */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);
char *_strcpy(char *dest, char *src);
char *starts_with(const char *haystack, const char *needle);

/*string_1.c*/
int _putchar(char c);
void _puts(char *str);
int _strcmp(char *s1, char *s2);

/*string_2.c*/
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);

/*enviroment_var.c*/
char *_getenv(info_st *info, const char *name);
int _myenv(info_st *info);
char **get_environ(info_st *info);
int populate_env_list(info_st *info);
int _mysetenv(info_st *);

/*enviroment_var1.c*/
int _setenv(info_st *info, char *var, char *value);
int _unsetenv(info_st *info, char *var);
int _myunsetenv(info_st *info);

/*list_string.c*/
size_t print_liststr(const list_st *h);
list_st *add_node(list_st **head, const char *str, int num);
list_st *add_node_end(list_st **head, const char *str, int num);
size_t print_list(const list_st *h);
list_st *node_starts_with(list_st *node, char *prefix, char c);

/*list_string1.c*/
int delete_node_at_index(list_st **head, unsigned int index);
ssize_t get_node_index(list_st *head, list_st *node);
char **list_to_strings(list_st *head);
size_t list_len(const list_st *h);

/*path.c*/
char *dup_chars(char *pathstr, int start, int stop);
char *get_path(info_st *info, char *pathstr, char *cmd);
int is_cmd(info_st *info, char *path);

/*function1.c*/
void print_error(info_st *info, char *estr);
int print_d(int input, int fd);
int is_delim(char c, char *delim);
int interactive(info_st *info);
char *convert_number(long int num, int base, int flags);

/*function2.c*/
void remove_comments(char *buf);
int _erratoi(char *s);

/*errstr_func.c*/
int _eputchar(char c);
void _eputs(char *str);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*fork.c*/
void fork_cmd(info_st *info);

/* info_st.c*/
void free_info(info_st *info, int all);

/* memory_func.c*/
int bfree(void **ptr);
void ffree(char **pp);
void free_list(list_st **head_ptr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memset(char *s, char b, unsigned int n);

/*hsh*/
int find_builtin(info_st *info);
int hsh(info_st *info, char **av);

/*builtin_commands.c*/
int _myexit(info_st *info);
int _myhelp(info_st *info);
int print_alias(list_st *node);
int _myalias(info_st *info);
int _mycd(info_st *info);

/*builtin_commands2.c*/
int _myhistory(info_st *info);
int unset_alias(info_st *info, char *str);
int set_alias(info_st *info, char *str);

/*io_functions.c*/
char *get_history_file(info_st *info);
int read_history(info_st *info);
int build_history_list(info_st *info, char *buf, int linecount);
int renumber_history(info_st *info);
int write_history(info_st *info);

/*stinfo.c*/
void set_info(info_st *info, char **av);
void clear_info(info_st *info);

/*chain.c*/
int is_chain(info_st *info, char *buf, size_t *p);
void check_chain(info_st *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_st *info);
int replace_vars(info_st *info);
int replace_string(char **old, char *new);

/*strtok.c*/
char **str_tok(char *str, char *d);
char **str_tok2(char *str, char d);

/*getline.c*/
void sigintHandler(__attribute__((unused))int sig_num);
int _getline(info_st *info, char **ptr, size_t *length);
ssize_t read_buf(info_st *info, char *buf, size_t *i);
ssize_t get_input(info_st *info);
ssize_t input_buf(info_st *info, char **buf, size_t *len);
#endif
