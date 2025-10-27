#ifndef UTILS_H
#define UTILS_H

char *utils_get_input();
void utils_get_path(char *cmd);
char *utils_get_command(char *input);
void utils_execute_command(char *cmd);
void utils_execute(char *string);
void utils_execute_program(char *cmd);

#endif
