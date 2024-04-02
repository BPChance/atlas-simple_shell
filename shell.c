#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

void read_input(char *input)
{
	fgets(input, MAX_INPUT_SIZE, stdin);
	input[strcspn(input, "\n")] = '\0';
}

void parse_input(char *input, char **tokens)
{
	char *token;
	int token_count = 0;

	token = strtok(input, " ");
	while (token != NULL && token_count < MAX_TOKENS - 1)
	{
		tokens[token_count] = token;
		token = strtok(NULL, " ");
		token_count++;
	}
	tokens[token_count] = NULL;
}

void execute_command(char **tokens)
{
	if (strcmp(tokens[0], "cd") == 0)
	{
		handle_cd(tokens);
	}
	else if ( strcmp(tokens[0], "exit") == 0)
	{
		handle_exit();
	}
	else
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execvp(tokens[0], tokens) < 0)
			{
				perror("Execution failed");
				exit(EXIT_FAILURE);
			}
		} 
		else
		{
			wait(NULL);
		}
	}
}

void handle_cd(char **tokens)
{
	if (tokens[1] == NULL)
	{
		fprintf(stderr, "cd: missing argument\n");
	}
	else
	{
		if ( chdir(tokens[1]) != 0)
		{
			perror("cd failed");
		}
	}
}

void handle_exit()
{
	exit(EXIT_SUCCESS);
}

int main() 
{
    char input[MAX_INPUT_SIZE];
    char *tokens[MAX_TOKENS];

    /* Shell loop */
    while (1) 
    {
        printf("$ ");
        fflush(stdout);

        read_input(input);
        parse_input(input, tokens);
        execute_command(tokens);
    }

    return 0;
}
