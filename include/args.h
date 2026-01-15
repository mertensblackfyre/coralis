#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

typedef struct args_t {
  int argc;
  char **argv;
  bool has_operator;
} args_t;

args_t *args_parse_arguments(char *input);

#endif
