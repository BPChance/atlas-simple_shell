#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void);
void tokenize_input(char *input, char **args);
void get_command(char **input);

#endif
