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

  for (size_t i = 0; i < size; ++i) {
    if (input[i] != '\t' && input[i] != ' ') {
      cmd[i] = input[i];
    } else {
      break;
    };
  };

  if (strncmp("exit", cmd, 4) == 0) {
    char **s = get_args(input);
    int n = atoi((char *)s);
    coralis_exit(n);
    return true;
  };
  if (strncmp("echo", cmd, 4) == 0) {
    char **s = get_args(input);
    coralis_echo(s);
    return true;
  };
  if (strncmp("pwd", cmd, 3) == 0) {
    coralis_pwd();
    return true;
  };
  if (strncmp("cd", cmd, 2) == 0) {
    char **s = get_args(input);
    coralis_cd(s);
    return true;
  };
  if (strncmp("type", cmd, 4) == 0) {
    char **s = get_args(input);
    if (coralis_type(s[1]))
      printf("%s is a shell builtin", s[1]);
    else
      get_path(s[1]);

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

  Args *args = malloc(sizeof(Args) * 500);
  size_t size = strlen(input);

  size_t cmd_size = strlen(get_cmd(input));

  char *word = (char *)malloc((30 + 1) * sizeof(char));

  args->data = (char **)malloc(200 * sizeof(char *));
  args->size = 0;

  int word_counter = 0;

  if (word == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  for (int i = cmd_size; i < size; ++i) {
    if (input[i] == '"') {
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
  return args;
};
