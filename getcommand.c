#include "getcommand.h"
#include "shell.h"
/**
 * get_command - read command from user
 * @input: buffer that stores user command
 * Return: void
 */

#define MAX_LENGTH 1024

void get_command(char **input)
{
	int interactive_mode;
	size_t input_size = 0;

	interactive_mode = isatty(STDIN_FILENO);

	if (interactive_mode)
	{
	printf("$ ");
	fflush(stdout);
	}
	/** error or eof */
	if (getline(input, &input_size, stdin) == -1)
	{
		free(*input);
		exit(EXIT_FAILURE);
	}

	(*input)[strcspn(*input, "\n")] = '\0';

/**	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			break;
		}
	} */
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
