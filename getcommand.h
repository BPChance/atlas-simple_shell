#ifndef COMMAND_H
#define COMMAND_H
#include "shell.h"
#include "getcommand.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


void tokenize_input(char *input, char **args, int *exit_flag);
void get_command(char **input);

#endif
