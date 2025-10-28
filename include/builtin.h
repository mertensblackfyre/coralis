#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdbool.h>

extern const char *builtin[];

bool builtin_check(char *input);
bool builtin_type(char *arg);
void builtin_exit(int status);
// void builtin_echo(Args *data);
void builtin_pwd();
// void builtin_cd(Args *args);

#endif
