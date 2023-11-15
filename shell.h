#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_tx;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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
	list_tx *env;
	list_tx *history;
	list_tx *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_tx;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_tx *);
} builtin_table;


/* simplesh_shelloop.c */
int funcname_hsh(info_tx *info, char **av);
int locatethe_builtin(info_tx *info);
void _find_command(info_tx *info);
void _fork_command(info_tx *info);

/* simplesh_parser.c */
int check_execmd(info_tx *info, char *path);
char *func_dupchars(char *pathstring, int start, int halt);
char *locate_path(info_tx *info, char *pathstring, char *cmd);

/* simplesh_loophsh.c */
int loophsh(char **);

/* simplesh_errors.c */
void inpu_str(char *str);
int write_stderr(char c);
int putcharfd(char k, int fd);
int func_putsfd(char *str, int fd);


/* simplesh_string.c */
int _stringretlen(char *g);
int _stringcomparison(char *Sa, char *Sb);
char *funcstarts_with(const char *haystack, const char *needle);
char *func_stringcat(char *destin, char *source);

/* simplesh_string1.c */
char *func_string_cpy(char *destin, char *srcs);
char *funcstringdup(const char *string);
void _funcinputs(char *strn);
int _writeputchar(char z);

/* simplesh_exits.c */
char *stringcopy(char *destination, char *source, int num);
char *string_concat(char *first, char *next, int n);
char *string_find(char *b, char c);

/* simplesh_tokenizer.c */
char **string_to_words(char *strn, char *w);
char **funcstring_tow2(char *strn, char w);

/* simplesh_realloc.c */
char *_memoryfill(char *v, char b, unsigned int x);
void _f_free(char **yy);
void *func_realloc(void *ptr, unsigned int oldsize, unsigned int newsize);

/* simplesh_memory.c */
int mem_free(void **poiter);

/* simplesh_atoi.c */
int _interactivion_mode(info_tx *infor);
int _is_delimeter(char k, char *delimeter);
int _its_alpha(int r);
int _atoi(char *str);

/* simplesh_errors1.c */
int convertoi(char *t);
void display_error(info_tx *info, char *estr);
int display_decimal(int input, int fd);
char *change_num(long int number, int base, int flags);
void delete_comments(char *buff);


/* simplesh_builtin.c */
int changes(info_tx *info);
int _my_changedir(info_tx *info);
int _my_program_exit(info_tx *info);

/* simplesh_builtin1.c */
int _my_cmd_history(info_tx *info);
int rem_alias(info_tx *info, char *str);
int pre_set_alias(info_tx *info, char *str);
int print_alias_string(list_tx *node);
int mimic_alias(info_tx *info);

/* simplesh_getline.c */
ssize_t _input_buffer(info_tx *info, char **buff, size_t *length);
ssize_t get_newlineinput(info_tx *info);
ssize_t func_readthebuff(info_tx *info, char *buffer, size_t *s);
int getnextline(info_tx *info, char **ptr, size_t *length);
void sig_nal_int_handler(__attribute__((unused))int signal_num);

/* simplesh_getinfo.c */
void init_info(info_tx *info);
void setclear_info(info_tx *info, char **av);
void free_info_struct(info_tx *info, int yes);

/* simplesh_environ.c */
int _myenvironment(info_tx *info);
char *get_environ_val(info_tx *info, const char *name);
int set_new_environ(info_tx *info);
int remove_setenv(info_tx *info);
int populatesthe_envlist(info_tx *info);


/* simplesh_getenv.c */
char **getmy_environ(info_tx *info);
int mv_setenv(info_tx *info, char *var);
int _set_newenv(info_tx *info, char *var, char *va_lue);

/* simplesh_history.c */
char *recieve_historyfile(info_tx *info);
int write_historyfile(info_tx *info);
int func_readhistory(info_tx *info);
int create_historylist(info_tx *info, char *buffer, int line_count);
int regivesnumber_history(info_tx *info);

/* simplesh_lists.c */
list_tx *the_headnode_add(list_tx **head, const char *string, int num);
list_tx *new_end_node(list_tx **head, const char *string, int num);
size_t _printliststr(const list_tx *u);
int deletethe_node_atindex(list_tx **head, unsigned int indexed);
void _freedlist(list_tx **headptr);

/* simplesh_lists1.c */
size_t _listleng(const list_tx *z);
char **return_arrstrings(list_tx *head);
size_t printthelist(const list_tx *z);
list_tx *nodethatbegins_with(list_tx *node, char *prefixer, char q);
size_t gets_the_nodeindex(list_tx *head, list_tx *node);


/* simplesh_vars.c */
int funct_ischain(info_tx *info, char *buff, size_t *z);
void checkifcontinue_chain(info_tx *info, char *buff, size_t *z, size_t a,
		size_t lenz);
int replac_etoken_alias(info_tx *info);
int change_vars(info_tx *info);
int change_string(char **old, char *new);

#endif
