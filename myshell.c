#include "shell.h"
/**
 * main - entry point
 * Return: 0
 */
#define MAX_LENGTH 1024
int main(void)
{
	pid_t pid;
	int i;
	char input[MAX_LENGTH];
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
			/** child process
			 * execute the command */
			execlp(input, input, NULL);
			/** if execlp returns, the command couldnt be executed */
			fprintf(stderr, "%s: command not found\n", input);
			exit(EXIT_FAILURE);
		}
		else
		{
			/** parent process
			 * wait for the child process to finish */
			wait(NULL);
		}
	}
	return (0);
}
