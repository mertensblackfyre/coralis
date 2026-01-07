#ifndef ARGS_H
#define ARGS_H

typedef struct args_t {
  int argc;
  char **argv;
} args_t;

args_t *args_parse_arguments(char *input);

#endif
