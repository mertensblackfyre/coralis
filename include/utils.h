#ifndef UTILS_H
#define UTILS_H


#include "parser.h"
bool has_args(const char* input);
int count_substrs(char *s);
char *backtrack_path(char *s, int count);
char *get_input();
void get_path(char *cmd);
void exe_cmd(char *cmd);
char *trim_space(char *string);
void exec(char *string);
void exe_program(char *cmd);
void find_program();
char *handle_str(Args *data);

#endif
