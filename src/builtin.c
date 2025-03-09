#include "../include/builtin.h"
#include "../include/utils.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 500
const char *builtin[] = {"echo", "type", "exit", "pwd", "cd"};

void coralis_cd(Args *args) {

  if (args->size == 0) {
    const char *env_variable = "HOME";
    char *value = getenv(env_variable);
    char *path = value;

    int err = chdir(path);
    return;
  };

  char *new_path = malloc(sizeof(char *) * SIZE);
  char *buffer = malloc(sizeof(char *) * SIZE);
  char *path = args->data[1];

  getcwd(buffer, SIZE);

  if (strstr(path, "../") != NULL) {
    int x = count_substrs(path);
    char *tmp = path;
    path = backtrack_path(buffer, x);
    strncat(path, tmp, strlen(tmp));
  };

  if (path[0] == '~') {
    const char *env_variable = "HOME";
    char *value = getenv(env_variable);
    path = value;
  };

  if (path[0] == '.') {
    for (int i = 1; i < strlen(path); ++i)
      new_path[i - 1] += path[i];

    strcat(buffer, new_path);
    path = buffer;
  }

  int err = chdir(path);

  if (err == -1) {
    if (errno == ENOENT)
      printf("Error: directory specified in path does not exist.");

    if (errno == EACCES)
      printf("Error: permission was denied.");

    if (errno == ENOTDIR)
      printf("Error: path is not a directory.");
  }
  return;
};

void coralis_pwd() {
  char *buffer = malloc(sizeof(char *) * SIZE);
  getcwd(buffer, SIZE);

  printf("%s", buffer);
};

void coralis_exit(int status) { exit(status); }

void coralis_echo(Args *data) {

  bool in_quote = false;
  char **message = data->data;
  for (size_t i = 1; i < data->size; ++i) {
    if (message[i] == NULL)
      continue;

    for (size_t j = 0; j < strlen(message[i]); ++j) {
      uintptr_t int_value = message[i][j];
      char *tmp = (char *)int_value;

      if ((message[i][j] == '"' || message[i][j] == '\'') && in_quote == true)
        in_quote = false;

      if ((message[i][j] == '"' || message[i][j] == '\'' )&& in_quote ==false) {
        in_quote = true;
        continue;
      };

      if (in_quote && message[i][j] == '\\') {
          printf("tr");
        //printf("\\");
        continue;
      }

      printf("%c", message[i][j]);
    }

    printf(" ");
  }
};

bool coralis_type(char *arg) {
  size_t size = sizeof(builtin) / sizeof(builtin[0]);

  for (size_t i = 0; i < size; ++i) {
    size_t arg_size = sizeof(&arg) / sizeof(arg[0]);
    size_t builtin_size = sizeof(&builtin[i]) / sizeof(builtin[i][0]);
    if (arg_size == builtin_size) {
      if (strncmp(trim_space(arg), builtin[i], arg_size) == 0) {
        return true;
      };
    }
  };

  return false;
}
