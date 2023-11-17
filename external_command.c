#include "shell.h"
/**
 * execute_External_command - executes external commands
 * @args: storage
 * Return: nothing
 */
void execute_External_command(char **args)
{
	int status;
	pid_t child_pid;

	if (access(args[0], X_OK) == -1)
	{
		perror("Command does not exist");
	}
	else
	{
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Fork failed");
		}
		else if (child_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Execve Error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}
}
