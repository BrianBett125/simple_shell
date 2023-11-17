#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <sys/types.h>

extern char **environ;

size_t my_strcspn(const char *string, const char *set);
char *my_strchr(const char *str, int c);
char *my_strncpy(char *strdest, const char *src, size_t n);
int my_strcmp(char *str1, char *str2);
void *my_realloc(void *ptr, unsigned int new_size);
void my_printf(const char *format, ...);
char *my_strdup(char *str);
int my_strlen(const char *strcnt);
void execute_Builtin_command(char **args);
void execute_External_command(char **args);
int main(int ac, char *av[]);
char **tokenize(char *buf);
#endif
