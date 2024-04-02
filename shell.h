#ifndef SHELL_H
#define ShELL_H
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

/* Function Prototypes */
void read_input(char *input);
void parse_input(char *input, char **tokens);
void execute_command(char **tokens);
void handle_cd(char **tokens);
void handle_exit();

#endif /* SHELL_H */
