#include "../include/parser.h"
#include "../include/builtin.h"
#include "../include/utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool isbuiltin(char *input) {

  size_t size = strlen(input);
  char cmd[100];

  Args *args = get_args(input);

  for (size_t i = 0; i < size; ++i) {
    if (input[i] != '\t' && input[i] != ' ') {
      cmd[i] = input[i];
    } else {
      break;
    };
  };

  if (strncmp("exit", cmd, 4) == 0) {
    if (args->size == 0) {
      coralis_exit(1);
      return true;
    }
    int n = atoi((char *)args->data);
    coralis_exit(n);
    return true;
  };
  if (strncmp("echo", cmd, 4) == 0) {
    coralis_echo(args);
    return true;
  };
  if (strncmp("pwd", cmd, 3) == 0) {
    coralis_pwd();
    return true;
  };
  if (strncmp("cd", cmd, 2) == 0) {
    coralis_cd(args);
    return true;
  };
  if (strncmp("type", cmd, 4) == 0) {
    if (coralis_type(args->data[1]))
      printf("%s is a shell builtin", args->data[1]);
    else
      get_path(args->data[1]);

    return true;
  };

  return false;
};

char *get_cmd(char *input) {
  size_t size = strlen(input);

  char *cmd = (char *)malloc((30 + 1) * sizeof(char));

  int char_counter = 0;
  if (cmd == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  for (int i = 0; i < size; ++i) {
    if (input[i] == '"')
      continue;

    if (isspace(input[i]) == 0)
      cmd[char_counter++] = input[i];
    else
      return cmd;
  };

  return cmd;
};

Args *get_args(char *input) {

  char *ar[300] = {};
  size_t size = strlen(input);
  Args *args = malloc(sizeof(Args));
  size_t cmd_size = strlen(get_cmd(input));

  int k = 0;
  bool in_single_quote = false;
  bool in_double_quote = false;

  if (args == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  if (has_args(input))
    return args;

  char *word = (char *)malloc((30 + 1) * sizeof(char));
  // args->data = (char **)malloc(200 * sizeof(char *));
  // args->size = 0;
  int word_counter = 0;

  if (word == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  for (int i = cmd_size + 1; i < size; ++i) {
    if (isspace(input[i])) {
      word[word_counter] = '\0';
      //ar[k] = (char *)malloc((word_counter + 1) * sizeof(char));

      // args->data[args->size] =
      //  (char *)malloc((word_counter + 1) * sizeof(char));
      /*
            if (args->data[args->size] == NULL) {
              fprintf(stderr, "Memory allocation failed for word %d\n", i);
              exit(1);
            }
            */
     strcpy(ar[k++], word);
      word_counter = 0;
    } else {
      word[word_counter++] = input[i];
    }
  };

  if (word_counter > 0) {

   // strcpy(ar[k++], word);
    // args->data[args->size] = (char *)malloc((strlen(word) + 1) *
    // sizeof(char));
    // strcpy(args->data[args->size++], word);
  }
  printf("%s", ar[0]);
  return args;
};

/*
Args *get_args(char *input) {

  size_t size = strlen(input);
  Args *args = malloc(sizeof(Args) * 500);

  bool in_single_quote = false;
  bool in_double_quote = false;

  if (args == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  if (has_args(input))
    return args;

  size_t cmd_size = strlen(get_cmd(input));

  char *word = (char *)malloc((30 + 1) * sizeof(char));
  args->data = (char **)malloc(200 * sizeof(char *));
  args->size = 0;
  int word_counter = 0;

  if (word == NULL || args->data == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  for (int i = cmd_size; i < size; ++i) {

    if (input[i] == '\'' && !in_double_quote) {
      in_single_quote = !in_single_quote;
      continue;
    }
    if (input[i] == '"' && !in_single_quote) {
      in_double_quote = !in_double_quote;
      continue;
    }

    if (input[i] == '\\' && isspace(input[i + 1])) {
      word[word_counter++] = input[i];
      word[word_counter++] = input[++i];
      continue;
    }
    if (isspace(input[i]) == 0) {
      word[word_counter++] = input[i];
    } else {
      word[word_counter] = '\0';
      args->data[args->size] =
          (char *)malloc((word_counter + 1) * sizeof(char));

      if (args->data[args->size] == NULL) {
        fprintf(stderr, "Memory allocation failed for word %d\n", i);
        exit(1);
      }
      strcpy(args->data[args->size++], word);
      word_counter = 0;
    }
  };

  args->data[args->size] = (char *)malloc((strlen(word) + 1) * sizeof(char));
  strcpy(args->data[args->size++], word);

  printf("%s", args->data[1]);
  // free(word);
  return args;
};
*/
