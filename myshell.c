#include "shell.h"
#include <unistd.h>
/**
 * main - entry point
 * Return: 0
 */
#define MAX_LENGTH 1024

extern char **environ;

int main(void)
{
	char *input = NULL;
	char *args[MAX_LENGTH];
	pid_t pid;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		/** get_command from getcommand.c */
		get_command(&input);
		/** tokenize_input from getcommand.c */
		tokenize_input(input, args);

		if (input == NULL || args[0] == NULL || strlen(args[0]) == 0)
		{
			free(input);
			input = NULL;
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		/** fork a child process */
		pid = fork();

		if (pid < 0)
		{
			perror("fork");
		/*	free(*input); */
			exit(EXIT_FAILURE);
		}
	       	else if (pid == 0)
		{
			/** child process */
			/** use execve and pass environ */
			execve(args[0], args, environ);

			/*if execve returns, command couldnt be executed */
			perror("execve");
		/*	free(*input); */
			exit(EXIT_FAILURE);
		}
		else
		{
			/** parent process */
			/** wait for the child process to finish unless it's a background process */
			if (!is_background(args[0]))
				waitpid(pid, &status, 0);
			else
				wait(NULL);
		}
		free(input);
		input = NULL;
	}
   	return (0);
}

/**
 * is_background - determines whether command should be
 * executed as a background process
 * @args: command to be executed
 * Return: 0
 */
int is_background(char *args)
{
	int i = 0;
	/* find end of string */
	while (args[i] != '\0')
		i++;

	if (i == 0)
		return (0);

	/* check if last character is '&' and return 1 if background process */
	if (args[i - 1] == '&')
		return (1);
	/* not a background process */
	return (0);
}
