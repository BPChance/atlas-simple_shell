#include "shell.h"
/**
 * main - entry point
 * Return: 0
 */
#define MAX_LENGTH 1024
int main(void)
{
	char input[MAX_LENGTH];
	/** Infinite loop to prompt user til they exit */
	while (1)
	{
		printf("$ ");
		fflush(stdout);

		/** if fgets fails it will print an error message and a failure status */
		if (fgets(input, MAX_LENGTH, stdin) == NULL)
		{
			perror("fgets failed");
			exit(EXIT_FAILURE);
		}
		printf("You entered: %s", input);
	}
	return (0);
}
