#include "shell.h"
#include "getcommand.h"
#include <unistd.h>
/**
 * main - entry point
 * Return: 0
 */
#define MAX_LENGTH 1024

extern char **environ;

int main(void)
{
	char input[MAX_LENGTH];
	char *args[MAX_LENGTH];
	pid_t pid;

	while (1)
	{
	/**	printf("$ "); */
		/** get_command from getcommand.c */
		get_command(input);
		/** tokenize_input from getcommand.c */
		tokenize_input(input, args);

		/** fork a child process */
		pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	       	else if (pid == 0)
		{
			/** child process */
			/** use execve and pass environ */
			execve(args[0], args, environ);
			/** if execve returns, the command couldnt be executed */
			fprintf(stderr, "%s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			/** parent process */
			/** wait for the child process to finish unless it's a background process */
			if (args[1] == NULL || strcmp(args[1], "&") != 0)
				wait(NULL);
		}
	}
    return (0);
}
