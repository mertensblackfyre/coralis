

#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "../include/args.h"

void args_parse_arguments(char *input) {

  char *argss[] = {NULL};
  int size = strlen(input);
  char *word = malloc(sizeof(size));
  int p = 0;

  for (int i = 0; i < size; i++) {
    if (isspace(input[i]) != 0) {
      argss[p++] = word;
      printf("%s", word);
      continue;
    }

    word += input[i];
  }
};
