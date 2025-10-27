#ifndef ARGS_H
#define ARGS_H

typedef struct Args_T {
    int argc;
    char *argv[];
} Args_T;


void args_parse_arguments(char *input);



#endif
