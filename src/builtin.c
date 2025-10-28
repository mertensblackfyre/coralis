#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/helper.h"
#include "../include/args.h"
#define SIZE 500
const char *builtin[] = {"echo", "type", "exit", "pwd", "cd"};

/*
bool isbuiltin(char *input) {

  size_t size = strlen(input);
  char cmd[100];

  char **args = args_parse_arguments(input);

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
*/
/*
void builtin_cd(Args *args) {

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
*/

void builtin_pwd() {
  char *buffer = malloc(sizeof(char *) * SIZE);
  if (getcwd(buffer, SIZE) == NULL)
    printf("error: Could not get path");

  printf("%s", buffer);
};

void builtin_exit(int status) { exit(1); }
/*
void builtin_echo(Args *data) { handle_str(data); };
*/
bool builtin_type(char *arg) {
  size_t size = sizeof(builtin) / sizeof(builtin[0]);

  for (size_t i = 0; i < size; ++i) {
    size_t arg_size = sizeof(&arg) / sizeof(arg[0]);
    size_t builtin_size = sizeof(&builtin[i]) / sizeof(builtin[i][0]);
    if (arg_size == builtin_size) {
      if (strncmp(helper_trim_space(arg), builtin[i], arg_size) == 0) {
        return true;
      };
    }
  };

  return false;
};
