#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

typedef struct Args {
  char **data;
  int size;
} Args;

bool isbuiltin(char *input);
int get_digit(char *input);
Args *get_args(char *input);
char *get_cmd(char *input);

#endif
