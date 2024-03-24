#include "shell.h"
/**
 * main - entry point
 * Return: 0
 */
#define MAX_LENGTH 1024

extern char **environ;

int main(void)
{
	pid_t pid;
	int i;
	char input[MAX_LENGTH];
	char *args[MAX_LENGTH];
	char *token;
	/** Infinite loop to prompt user til they exit */
	while (1)
	{
		printf("$ ");
		fflush(stdout);

		/** prints a newline if ctrl-d (eof) is encountered */
		if (fgets(input, MAX_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		/** removes newline from input */
		for (i = 0; input[i] != '\0'; i++)
		{
			if (input[i] == '\n')
			{
				input[i] = '\0';
				break;
			}
		}
		/** tokenize input */
		token = strtok(input, " ");

		i = 0;

		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		/** check for built in commands */;
		if (strcmp(args[0], "exit") == 0)
			break;
		/** fork a child process */
		pid = fork();
		
		if (pid < 0)
		{
			/** error handling if the fork fails */
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/** child process */
			/** usage of environ in execve */
			execve(args[0], args, environ);
			/** if execve returns, the command couldnt be executed */
			fprintf(stderr, "%s: command not found\n", input);
			exit(EXIT_FAILURE);
		}
		else
		{
			/** parent process
			 * wait for the child process to finish */
			if (args[i - 1][0] != '&')
				wait(NULL);
		}
	}
	return (0);
}
