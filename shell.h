#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer Sizes */
#define CUSTOM_READ_BUF_SIZE 1024
#define CUSTOM_WRITE_BUF_SIZE 1024
#define CUSTOM_BUF_FLUSH -1

/* Command Chaining */
#define CUSTOM_CMD_NORM    0
#define CUSTOM_CMD_OR      1
#define CUSTOM_CMD_AND     2
#define CUSTOM_CMD_CHAIN   3

/* Number Conversion Options */
#define CUSTOM_CONVERT_LOWERCASE   1
#define CUSTOM_CONVERT_UNSIGNED    2

/* Use of system getline() and strtok */
#define CUSTOM_USE_GETLINE 0
#define CUSTOM_USE_STRTOK 0

/* History Configuration */
#define CUSTOM_HIST_FILE    ".custom_shell_history"
#define CUSTOM_HIST_MAX    4096

extern char **environ;

/**
 * struct custom_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct custom_liststr
{
    int num;
    char *str;
    struct custom_liststr *next;
} custom_list_t;

/**
 * struct custom_passinfo - contains pseudo-arguments for functions
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from args
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit() calls
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last executed command
 * @cmd_buf: address of pointer to cmd chain buffer
 * @cmd_buf_type: command type (||, &&, ;)
 * @readfd: the file descriptor from which to read line input
 * @histcount: the history line number count
 */
typedef struct custom_passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    custom_list_t *env;
    custom_list_t *history;
    custom_list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} custom_info_t;

#define CUSTOM_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * struct custom_builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct custom_builtin
{
    char *type;
    int (*func)(custom_info_t *);
} custom_builtin_table;

/* Function Declarations */
int custom_hsh(custom_info_t *, char **);
int custom_find_builtin(custom_info_t *);
void custom_find_cmd(custom_info_t *);
void custom_fork_cmd(custom_info_t *);
int custom_is_cmd(custom_info_t *, char *);
char *custom_dup_chars(char *, int, int);
char *custom_find_path(custom_info_t *, char *, char *);
int custom_loophsh(char **);
void custom_eputs(char *);
int custom_eputchar(char);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void custom_puts(char *);
int custom_putchar(char);
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);
char **custom_strtow(char *, char *);
char **custom_strtow2(char *, char);
char *custom_memset(char *, char, unsigned int);
void custom_ffree(char **);
void *custom_realloc(void *, unsigned int, unsigned int);
int custom_bfree(void **);
int custom_interactive(custom_info_t *);
int custom_is_delim(char, char *);
int custom_isalpha(int);
int custom_atoi(char *);
int custom_erratoi(char *);
void custom_print_error(custom_info_t *, char *);
int custom_print_d(int, int);
char *custom_convert_number(long int, int, int);
void custom_remove_comments(char *);
int custom_myexit(custom_info_t *);
int custom_mycd(custom_info_t *);
int custom_myhelp(custom_info_t *);
int custom_myhistory(custom_info_t *);
int custom_myalias(custom_info_t *);
ssize_t custom_get_input(custom_info_t *);
int custom_getline(custom_info_t *, char **, size_t *);
void custom_sigintHandler(int);
void custom_clear_info(custom_info_t *);
void custom_set_info(custom_info_t *, char **);
void custom_free_info(custom_info_t *, int);
char *custom_getenv(custom_info_t *, const char *);
int custom_myenv(custom_info_t *);
int custom_mysetenv(custom_info_t *);
int custom_myunsetenv(custom_info_t *);
int custom_populate_env_list(custom_info_t *);
char **custom_get_environ(custom_info_t *);
int custom_unsetenv(custom_info_t *, char *);
int custom_setenv(custom_info_t *, char *, char *);
char *custom_get_history_file(custom_info_t *info);
int custom_write_history(custom_info_t *info);
int custom_read_history(custom_info_t *info);
int custom_build_history_list(custom_info_t *info, char *buf, int linecount);
int custom_renumber_history(custom_info_t *info);
custom_list_t *custom_add_node(custom_list_t **, const char *, int);
custom_list_t *custom_add_node_end(custom_list_t **, const char *, int);
size_t custom_print_list_str(const custom_list_t *);
int custom_delete_node_at_index(custom_list_t **, unsigned int);
void custom_free_list(custom_list_t **);
size_t custom_list_len(const custom_list_t *);
char **custom_list_to_strings(custom_list_t *);
size_t custom_print_list(const custom_list_t *);
custom_list_t *custom_node_starts_with(custom_list_t *, char *, char);
ssize_t custom_get_node_index(custom_list_t *, custom_list_t *);
int custom_is_chain(custom_info_t *, char *, size_t *);
void custom_check_chain(custom_info_t *, char *, size_t *, size_t, size_t);
int custom_replace_alias(custom_info_t *);
int custom_replace_vars(custom_info_t *);
int custom_replace_string(char **, char *);

#endif

