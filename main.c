#include "shell.h"
/**
 * main - function that starts the program
 * @ac: argument count
 * @av: argument vector
 * Return: void
 */
int main(int ac, char *av[])
{
	char **args;
	char *buf = NULL;
	size_t buf_size = 0;
	int a;

	if (ac > 1)
	{
		for (a = 1; a < ac; a++)
		{
			args = tokenize(av[a]);
			if (args != NULL)
			{
				execute_Builtin_command(args);
				execute_External_command(args);
				free(args);
			}
		}
	} else
	{
		while (1)
		{
			write(1, "$ ", 2);
			if (getline(&buf, &buf_size, stdin) == -1)
			{
				perror("Error reading input");
				break;
			} args = tokenize(buf);
			if (args != NULL)
			{
				execute_Builtin_command(args);
				execute_External_command(args);
				free(args);
			}
			free(buf);
			buf = NULL;
			buf_size = 0;
		}
	}
	free(buf);
	return (0);
}
