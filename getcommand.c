#include "shell.h"
/**
 * get_command - read command from user
 * @input: holds the memory address of a dynamically allocated
 * string where the user input will be stored
 * Return: void
 */

#define MAX_LENGTH 1024

void get_command(char **input)
{
	size_t input_size = 0;
	int input_length;

	*input = NULL;

	input_length = getline(input, &input_size, stdin);
	/** error or eof */
	if (input_length == -1)
	{
			/* input = NULL; */
			free(*input);
			exit(EXIT_SUCCESS);
	}
	else
	{
		/* replace newline with null terminator */
		(*input)[input_length - 1] = '\0';
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

	while (token != NULL && i < MAX_LENGTH - 1)
	{
		/* store token in args array */
		args[i++] = token;
		/* get next token */
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
