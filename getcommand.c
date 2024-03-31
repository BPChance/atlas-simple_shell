#include "shell.h"
/**
 * get_command - read command from user
 * @input: buffer that stores user command
 * Return: void
 */

#define MAX_LENGTH 1024

ssize_t get_command(void)
{
	char *input_buffer = NULL;
	size_t input_size = 0;
	ssize_t input_length;

	input_length = getline(&input_buffer, &input_size, stdin);
	/** error or eof */
	if (input_length == -1)
	{
		if (feof(stdin))
		{
			/* input = NULL; */
			free(input_buffer);
			printf("End of input reached");
			exit(EXIT_SUCCESS);
		}
		else
		{
		perror("getline");
		free(input_buffer);
		}
	}
	else
	{
		input_buffer[input_length - 1] = '\0';
	}
	free(input_buffer);
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
	char *token, *arg_token;
	int i = 0;

	token = strtok(input, " ");

	while (token != NULL && i < MAX_LENGTH - 1)
	{
		if (token[0] == '/')
			args[i++] = token;

		else
		{
			arg_token = strtok(token, " ");

			while (arg_token != NULL && i < MAX_LENGTH - 1)
			{
				args[i++] = arg_token;
				arg_token = strtok(NULL, " ");
			}
		}
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
