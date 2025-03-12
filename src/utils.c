#include "../include/parser.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 20240

char *handle_str(Args *data) {

  char *s = "a";

  for (int i = 0; i < data->size; ++i) {

    printf("%s", data->data[i]);
  }
  return s;
};

bool has_args(char *input) {
  int count = 0;
  size_t size = strlen(input);
  for (int i = 0; i < size; ++i)
    if (input[i] == ' ')
      count++;

  return count == 0;
};

char *backtrack_path(char *s, int count) {
  size_t len = strlen(s);
  for (int i = len; i > 0; --i) {
    if (s[i] == '/')
      count--;
    if (count > 0)
      s[i] = '\0';
  };
  return s;
};

int count_substrs(char *s) {

  size_t size = strlen(s);
  int count = 0;

  while ((s = strstr(s, "../")) != NULL) {
    count++;
    memmove(s, s + 3, strlen(s + 3) + 1);
  };
  return count;
};

char *get_input() {
  char *input = malloc(sizeof(char) * 100);
  char *s = fgets(input, 100, stdin);
  input[strlen(input) - 1] = '\0';

  return input;
};

void get_path(char *cmd) {
  int fd[2];
  int fd_err[2];
  int fd_pipe = pipe(fd);
  int fd_err_pipe = pipe(fd_err);

  char buffer[BUFFER_SIZE];
  char path[256] = "/usr/bin/";
  strcat(path, cmd);

  pid_t pid = fork();

  if (pid == 0) {
    dup2(fd[1], STDOUT_FILENO);
    dup2(fd_err[1], STDERR_FILENO);
    char *args[] = {"which", cmd, NULL};
    execvp("which", args);

    // If execvp fails, print an error and exit
    perror("execvp");
    exit(1);
  } else {

    // Close unused pipe ends
    close(fd[1]);
    close(fd_err[1]);

    size_t size = read(fd[0], buffer, BUFFER_SIZE);
    buffer[size - 1] = '\0';

    if (size != 0) {
      printf("%s is in %s", cmd, buffer);
      return;
    }
    printf("%s: not found", cmd);

    return;
  };
  return;
};

char *trim_space(char *string) {
  size_t size = sizeof(&string) / sizeof(string[0]);
  int i = 0;
  while (isspace(string[i]) && i < size) {
    char a, tmp;
    tmp = string[i];
    a = string[i + 1];
    string[i] = a;
    string[i + 1] = tmp;
    i++;
  }
  return string;
};

void exe_program(char *input) {

  Args *args = get_args(input);
  char *cmd = get_cmd(input);

  if (strlen(cmd) == 0) {
    return;
  };

  char buffer[BUFFER_SIZE];
  int fd[2];
  int fd_err[2];
  int fd_pipe = pipe(fd);
  int fd_err_pipe = pipe(fd_err);

  pid_t cpid = fork();
  if (cpid == -1) {
    perror("fork()");
  };

  if (cpid == 0) {
    dup2(fd[1], STDOUT_FILENO);
    dup2(fd_err[1], STDERR_FILENO);
    execvp(cmd, args->data);
    printf("%s: command not found", cmd);
    return;
  } else {
    close(fd[1]);
    close(fd_err[1]);

    size_t size = read(fd[0], buffer, BUFFER_SIZE);
    buffer[size - 1] = '\0';
    printf("%s", buffer);
    return;
  };

  printf("Unknown arguments");

  if (kill(cpid, SIGTERM) == 0) {
    return;
  } else {
    perror("Error terminating child process");
  };
};
