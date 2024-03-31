#include "shell.h"
/**
 * get_command - read command from user
 *
 * Return: void
 */

#define MAX_LENGTH 1024

int get_command(char *input)
{
	size_t input_size = 0;
	int input_length;

	input = NULL;

	input_length = getline(&input, &input_size, stdin);
	/** error or eof */
	if (input_length == -1)
	{
		if (feof(stdin))
		{
			/* input = NULL; */
			free(input);
			printf("End of input reached");
			exit(EXIT_SUCCESS);
		}
		else
		{
		perror("getline");
		free(input);
		}
	}
	else
	{
		input[input_length - 1] = '\0';
	}
	free(input);
	return (input_length);
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
