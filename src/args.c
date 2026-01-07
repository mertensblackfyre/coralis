

#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "../include/args.h"

args_t *args_parse_arguments(char *input) {

  int size = strlen(input);
  args_t *args = calloc(1, sizeof(args_t));

  char word[size + 1];
  args->argv = (char **)malloc(size * 2 * sizeof(char *));

  char **args_p = args->argv;
  if (args->argv == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  };

  int wordc = 0;
  char *word_p;

  word_p = &word[0];

  for (int i = 0; i < size; ++i) {
    if (!isspace(input[i])) {
      *word_p = input[i];
      word_p++;
      wordc++;
    } else {
      *word_p = '\0';
      *args->argv = malloc((wordc + 1) * sizeof(char *));
      if (*args->argv == NULL) {
        fprintf(stderr, "Memory allocation failed for word %d\n", i);
        exit(EXIT_FAILURE);
      }
      strncpy(*args->argv, word, wordc);
      args->argc++;
      args->argv++;
      word_p = &word[0];
      wordc = 0;
    }
  };

  *word_p = '\0';
  *args->argv = malloc((wordc + 1) * sizeof(char *));
  if (*args->argv == NULL) {
    fprintf(stderr, "Memory allocation failed for word\n");
    exit(EXIT_FAILURE);
  }
  strncpy(*args->argv, word, strlen(word));
  args->argc++;
  args->argv = args_p;
  
  return args;
};
