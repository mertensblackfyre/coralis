#ifndef UTILS_H
#define UTILS_H

#include "./args.h"
char *utils_get_input();
void utils_get_path(char *cmd);
char *utils_get_command(char *input);
void utils_execute_command(char *cmd);
void utils_execute(char *string);
void utils_execute_program(char *cmd);
void utils_redirect_stdout(const char *buffer, const args_t *args);
#endif
