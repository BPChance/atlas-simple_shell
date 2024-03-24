#include "getcommand.h"
#include "shell.h"
/**
 *
 */

#define MAX_LENGTH 1024

void get_command(char *input)
{
	int i;

	printf("$ ");
	fflush(stdout);

	if (fgets(input, MAX_LENGTH, stdin) == NULL)
	{
		printf("\n");
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
 *
 */
void tokenize_input(char *input, char **args)
{
	char *token = strtok(input, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

}
