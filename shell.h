#ifndef SHEiLL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*read/write buffer*/
#define READ_BUFF_S 1024
#define WRITE_BUFF_S 1024
#define BUFF_FLUSH -1

/* command chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert numbers */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* using system getline()*/
#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct list_str - linked list
 * @numb: number of field
 * @str: string
 * @next: pointer to the next node
 */
typedef struct list_str
{
	int numb;
	char *str;
	struct list_str *next;
}
list_t;

/**
 * struct passinfo -  contains pseudo-arguments for a function
 * @arg: string generated from getline
 * @argv: array of strings generated from arg
 * @path: path for the current command
 * @argc: argument count
 * @err_num: error code for exit
 * @line_count: error count
 * @fname: program file name
 * @linecount_flag: count this line of input if on
 * @environ: modified copy fo environ from LL env
 * @env: linked list
 * @history: history node
 * @status: return status of exe'd command
 * @cmd_buf: pointer to cmd_buf's address
 * @cmd_buf_type: CMD type or, &&
 * @readfd: file directory from which to read line input
 * @histcount: line count history
 * @alias: alias node
 * @env_changed: on if envrion was changed
 */

typedef struct passinfo {

	char *arg;
	char *path;
	int argc;
	char **argv;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	unsigned int line_count;
	list_t *env;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, 0, NULL, 0, 0, 0, NULL, NULL, NULL, 0, 0, 0, NULL, NULL, \
	0, 0, 0}

/**
 * struct builtin - conatian builtin string
i * @type: builtin command flag
 *
 * @func: function
 */
typedef struct builtin
{
	char *type;
int (*func)(info_t *);
}
builtin_table;

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_char(char *, int, int);
char *find_path(info_t *, char *, char *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

int loophsh(char **);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

int bfree(void **);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

char **strtow(char *, char *);
char **strtow2(char *, char);

int intrctiv(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int myexit(info_t *);
int mycd(info_t *);
int _myhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void signHand(int);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
#endif /*SHELL_H*/
