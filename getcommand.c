#include "getcommand.h"
#include "shell.h"
/**
 * get_command - read command from user
 * @input: buffer that stores user command
 * Return: void
 */

#define MAX_LENGTH 1024

void get_command(char *input)
{
	int i, interactive_mode;

	interactive_mode = isatty(fileno(stdin));

	if (interactive_mode)
	{
	printf("$ ");
	fflush(stdout);
	}

	if (fgets(input, MAX_LENGTH, stdin) == NULL)
	{
		exit(EXIT_SUCCESS);
	}

	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			break;
		}
	}
}

/**
 * tokenize_input - tokenize user input
 * @input: input to be tokenized
 * @args: arguments
 * Return: void
 */
void tokenize_input(char *input, char **args)
{
	char *token;
	int i = 0;

	token = strtok(input, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL;
}
