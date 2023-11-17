#include "shell.h"
/**
 * execute_Builtin_command - executes builtin commands
 * @args: argument
 * Return: nothing
 */
void execute_Builtin_command(char **args)
{
	char **env = environ;
	int a;

	while (args[a] != NULL)
	{
		a++;
	}
	if (my_strcmp(args[0], "cd") == 0)
	{
		if (chdir(args[1]) < 0)
		{
			perror("Error with cd");
		}
	}
	else if (my_strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (my_strcmp(args[0], "env") == 0)
	{

		while (*env != NULL)
		{
			my_printf("%s\n", *env);
			env++;
		}
	}
}
