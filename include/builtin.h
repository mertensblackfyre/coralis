#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdbool.h>

extern const char *builtin[];

bool coralis_type(char *arg);
void coralis_exit(int status);
void coralis_echo(char **messeage);
void coralis_pwd();

void coralis_cd(char **arg);
#endif
