#ifndef _SIMPLESHELL_H
#define _SIMPLESHELL_H


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

/* Buffer sizes intended for writing as well as reading */

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

/* Command chaining options */
#define CHAIN_NORMAL    0
#define CHAIN_OR        1
#define CHAIN_AND       2
#define CHAIN_PIPE      3

/* Flags for number conversion */
#define CONVERT_TO_LOWER     1
#define CONVERT_TO_UNSIGNED  2

/* Flags indicating usage of system's getline() */
#define USE_SYSTEM_GETLINE   0
#define USE_SYSTEM_STRTOK    0

/* History file and max size */
#define HISTORY_FILE     ".shell_history"
#define MAXIMUM_HISTORY_ENTERIES 4096

extern char **environ;

/**
 * struct list_item - item in a linked list.
 * @number: num of item in the list
 * @value: ptr to a str having the value linked to the item
 * @next: ptr to the next item
 */
typedef struct list_item
{
	int number;
	char *value;
	struct list_item *next;
} list_item_t;


/**
 * struct shellinfo - stores information needed for command execution
 *                     within a simple shell prog
 * @input:          the raw input string from the user.
 * @args:           the parsed array of args taken from input
 * @current_path:      the resolved path for the current command
 * @arg_count:      the number of args parsed
 * @execline_count:     the total num of commands executed, error tracking
 * @errexit_code:      the exit code from the last executed cmd
 * @countflag_input:    flag to indicate if current input should be counted
 * @program_name:   the name of the shell prog
 * @env_list:       a linked list showing shell's env vars
 * @env_array:      an array of env vars.
 * @cmd_history:    the history of executed cmds
 * @aliases:        linked list of cmd aliases.
 * @env_modified:   flag showing if env have been altered
 * @last_status:    status code of last executed cmd
 * @buffer:         ptr to the cmd buff, for cmd chaining
 * @buffer_type:    type of cmd chaining (, '||', '&&', ';')
 * @input_fd:       file descriptor for input
 * @history_count:  num of cmds in history list.
 */
typedef struct shellinfo
{
	char *input;
	char **args;
	char *current_path;
	int arg_count;
	unsigned int execline_count;
	int errexit_code;
	int countflag_input;
	char *program_name;
	list_item_t *env_list;
	char **env_array;
	list_item_t *cmd_history;
	list_item_t *aliases;
	int env_modified;
	int last_status;
	char **buffer;
	int buffer_type;
	int input_fd;
	int history_count;
} shellinfo_t;

#define  INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - associates a builtin cmd with its function
 * @command: the name of builtin cmd
 * @func: the function that impliments the builtin cmd
 */
typedef struct builtin
{
	char *command;
	int (*func)(shellinfo_t *);
} builtin_table;



/* buff_input.c */
ssize_t buff_input(shellinfo_t *sdata, char **buff, size_t *bulen);


/* builtin_handlers.c */
int simshell_exit(shellinfo_t *shell_info);
int shell_curdir(shellinfo_t *shell_info);
int simshell_help(shellinfo_t *shell_info);

/* command_chaining.c */
int change_string(char **prev_str, char *curr_str);
int change_vars(shellinfo_t *inf);
int change_aliases(shellinfo_t *inf);
void chk_cmd_chain(shellinfo_t *inf, char *buff, size_t *indx, size_t strt, size_t buf_l);
int cmd_chain(shellinfo_t *shell_info, char *buff, size_t *pos);

/*  data.c */

void clr_shedata(shellinfo_t *sdata);
void config_data(shellinfo_t *sdata, char **argvec);
void release_shdata(shellinfo_t *shell_info, int freeall);

/* simshell_main.c */
int main(int arg_cnt, char **arg_val);

/* envir.c */
int output_envir(shellinfo_t *shell_info);
char *get_envval(shellinfo_t *shell_info, const char *varbl_name);
int set_enviro_var(shellinfo_t *shell_info);
int remove_env_var(shellinfo_t *shell_info);
int pop_envlist(shellinfo_t *shell_info);

/* envir2.c */
char **fetch_env(shellinfo_t *shell_data);
int unset_envir(shellinfo_t *shell_data, char *envi_var);
int assign_env(shellinfo_t *shell_data, char *envi_vari, char *env_val);

/* file_io_helpers.c */

char *retrieve_hist(shellinfo_t *sdata);
int w_hist(shellinfo_t *sdata);
int r_hist(shellinfo_t *sdata);
int add_to_history(shellinfo_t *sdata, char *buff, int linec);
int updhistory_num(shellinfo_t *sdata);

/* _get_ln.c */
ssize_t _getinpu(shellinfo_t *sdata);
int gt_(shellinfo_t *sdata, char **screen, size_t *sze);
void sigint(int dt);
ssize_t r_bufff(shellinfo_t *sdata, char *screen, size_t *sze);

/* more_builtin_handlers.c */
int display_history(shellinfo_t *shell_info);
int erase_alias(shellinfo_t *shell_info, char *alias_string);
int allot_alias(shellinfo_t *shell_info, char *alias_string);
int output_alias(list_item_t *alias_n);
int sshell_alias(shellinfo_t *shell_info);

/* string_list.c */

list_item_t *appnd_nd(list_item_t **hd, const char *string, int ber);
list_item_t *app_ndend(list_item_t **hd, const char *string, int ber);
size_t output_lisval(const list_item_t *hd);
int remove_nd_idx(list_item_t **hd, unsigned int idx);
void libre_list(list_item_t **hd_p);

/*  string_list2.c */

size_t lst_lng(const list_item_t *hd);
char **lst_str(list_item_t *hd);
size_t output_list(const list_item_t *hd);
list_item_t *nd_begin_with(list_item_t *nd, char *prfx, char r);
ssize_t aqu_nd_indx(list_item_t *hd, list_item_t *nd);

int is_interactive(shellinfo_t *info);
/* shell_strings.c*/
void _puts(char *string);
int _put_char(char ch);
int _str_length(char *str);

/* shell_strings2.c*/
char *_strd_up(const char *string);
char *_str_copy(char *desti, char *sorc);
char *start_with(const char *hstack, const char *needle);
int _str_cmp(char *str1, char *str2);
char *_str_cat(char *desti, char *sorc);

/* shell_strings3.c */
char *_strn_cpy(char *desti, char *sorc, int n);
char *_strn_cat(char *desti, char *sorc, int n);
char *_str_chr(char *str, char ch);

/* string_split.c */
char **split_string(char *string, char *delim);

/* helper_function.c */
int is_interactive(shellinfo_t *shell_info);
int is_delimeter(char c, char *d);
int error_atoi(const char *str);
void output_error(shellinfo_t *shell_info, char *estr);
int print_decimal(int input, int filed);

/* handle_errors.c */
void error_puts(char *string);
int error_putchar(char ch);
int _puts_filed(char *string, int filed);
int _puts_filed(char *string, int filed);

/*helper_function2.c */
char *convert_num(long int n, int base, int flags);
void remove_comm(char *buffer);

/* handle_memory.c */
char *_mem_set(char *str, char byte, unsigned int num);
void f_free(char **ptr);
void *_re_allocate(void *pointer, unsigned int old_s, unsigned int new_s);
int b_free(void **p);

/* path_handler.c */
int is_executable(shellinfo_t *shell_info, char *path);
char *dup_character(char *pathstr, int start, int stop);
char *search_path(shellinfo_t *shell_info, char *pathst, char *cmd);

/*hsh_loop.c */
int hsh(shellinfo_t *shell_info, char **argv);
int find_built_in(shellinfo_t *shell_info);
void find_command(shellinfo_t *shell_info);
void fork_command(shellinfo_t *shell_info);


#endif
