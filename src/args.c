

#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "../include/args.h"

Args_T *args_parse_arguments(char *input) {

  int size = strlen(input);
  Args_T *args_t = malloc(sizeof(Args_T));

  char *word = (char *)malloc((size + 1) * sizeof(char));
  args_t->argv = (char **)malloc(size * sizeof(char *));

  int wordc = 0;

  if (word == NULL || args_t->argv == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  };

  for (int i = 0; i < size; ++i) {
    if (isspace(input[i]) == 0) {
      word[wordc++] = input[i];
    } else {
      word[wordc] = '\0';
      args_t->argv[args_t->argc] = (char *)malloc((wordc + 1) * sizeof(char));

      if (args_t->argv[args_t->argc] == NULL) {
        fprintf(stderr, "Memory allocation failed for word %d\n", i);
        exit(1);
      }
      strncpy(args_t->argv[args_t->argc], word, wordc);
      args_t->argc++;
      wordc = 0;
    }
  };

  args_t->argv[args_t->argc] =
      (char *)malloc((strlen(word) + 1) * sizeof(char));

  if (args_t->argv[args_t->argc] == NULL) {
    fprintf(stderr, "Memory allocation failed for word\n");
    exit(1);
  }

  strncpy(args_t->argv[args_t->argc++], word, wordc);
  free(word);

  return args_t;
};
