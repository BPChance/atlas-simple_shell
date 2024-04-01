#include "shell.h"
/**
 * find_command_path - find full path of a command by searching
 * through directories in PATH
 * @command: string containing user input
 * Return: return NULL if command not found, returns a
 * string containing the full path if command is executable
 */

#define MAX_LENGTH 1024

char *find_command_path(char *command)
{
	char command_path[MAX_LENGTH];
	/* get value of PATH */
	char *path = getenv("PATH");
	/* copy of the PATH string to avoid modifying the original */
	char *path_copy = strdup(path);
	/* tokenize copied PATH string */
	char *dir = strtok(path_copy, ":");
	/* if command begins with / its already a full path */
	if (command[0] == '/')
	{
		/* check if path is executable */
		if (access(command_path, X_OK) == 0)
			return (strdup(command));
		else
			return (NULL);
	}
	/* iterate through each directory in PATH */
	while (dir != NULL)
	{
		strcpy(command_path, dir);
		/* separate directory and command */
		strcat(command_path, "/");
		strcat(command_path, command);
		/* check if path is executable */
		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(command_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
