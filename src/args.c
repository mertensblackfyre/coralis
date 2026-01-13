#include <ctype.h>
#include <stdio.h>

#include <stdbool.h>
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

  bool in_single_quote = false, in_double_quote = false;

  for (int i = 0; i < size; ++i) {
    if (input[i] == '"' && !in_double_quote) {
      in_double_quote = true;
      while (in_double_quote) {
        if (i < size) {
          i++;
          if (input[i] == '"' && in_double_quote) {
            in_double_quote = false;
            if (input[i + 1] == '"' && !in_double_quote) {
              i++;
              in_double_quote = true;
              continue;
            }
            break;
          }
          *word_p = input[i];
          word_p++;
          wordc++;
        } else {
          i++;
          continue;
        }
      };

      if (!in_double_quote && !in_single_quote) {
        i++;
        *word_p = '\0';
        *args->argv = malloc((wordc + 1) * sizeof(char *));
        if (*args->argv == NULL) {
          fprintf(stderr, "Memory allocation failed for word %d\n", i);
          exit(EXIT_FAILURE);
        };
        strncpy(*args->argv, word, wordc);
        args->argc++;
        args->argv++;
        word_p = &word[0];
        wordc = 0;
        continue;
      }
    };

    if (input[i] == '\'' && !in_single_quote) {
      in_single_quote = true;
      while (in_single_quote) {
        if (i < size) {
          i++;
          if (input[i] == '\'' && in_single_quote) {
            in_single_quote = false;
            if (input[i + 1] == '\'' && !in_single_quote) {
              i++;
              in_single_quote = true;
              continue;
            }
            break;
          }
          *word_p = input[i];
          word_p++;
          wordc++;
        } else {
          i++;
          continue;
        }
      };

      if (!in_single_quote && !in_double_quote) {
        i++;
        *word_p = '\0';
        *args->argv = malloc((wordc + 1) * sizeof(char *));
        if (*args->argv == NULL) {
          fprintf(stderr, "Memory allocation failed for word %d\n", i);
          exit(EXIT_FAILURE);
        };
        strncpy(*args->argv, word, wordc);
        args->argc++;
        args->argv++;
        word_p = &word[0];
        wordc = 0;
        continue;
      }
    };

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

  for (int i = 0; i < args->argc; ++i) {
    //  printf("%s\n", args->argv[i]);
  };

  printf("%d\n", args->argc);

  return args;
};
