#include "shell.h"
/**
 * tokenize - tokenizest the input
 * @buf: acts as storage
 * Return: args
 */
char **tokenize(char *buf)
{
	char *token;
	char **args = malloc(sizeof(char *) * 1024);
	int b = 0;

	token = strtok(buf, "\t\n");
	while (token)
	{
		args[b] = token;
		token = strtok(NULL, "\t\n");
		b++;
	}
	args[b] = NULL;
	return (args);
}
