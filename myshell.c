#include "shell.h"
#include "getcommand.h"
#include <unistd.h>
/**
 * main - entry point
 * Return: 0
 */
#define MAX_INPUT_SIZE 256

extern char **environ;

int main(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE];
	pid_t pid;
	int exit_flag = 0;
	int status;

	while (!exit_flag)
	{
		get_command(args);
		
		if (args[0] == NULL)
			continue;

		if (strcmp(args[0], "exit") == 0)
		{
			exit_flag = 1;
			continue;
		}

		pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	       	else if (pid == 0)
		{
			printf("Executing command: %s\n", args[0]);

			if (execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/** parent process */
			/** wait for the child process to finish unless it's a background process */
			if (args[1] == NULL || strcmp(args[1], "&") != 0)
				waitpid(pid, &status, 0);
		}
	}
	
	return (0);
}

