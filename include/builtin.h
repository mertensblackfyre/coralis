#ifndef BUILTIN_H
#define BUILTIN_H

#include "parser.h"
#include <stdbool.h>

extern const char *builtin[];

bool coralis_type(char *arg);
void coralis_exit(int status);
void coralis_echo(Args *data);
void coralis_pwd();

void coralis_cd(Args *args);
#endif
