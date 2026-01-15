#include "../include/utils.h"
#include "../include/args.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 10240

char *utils_get_input() {
  char *input = malloc(sizeof(char) * 100);
  char *s = fgets(input, 100, stdin);
  input[strlen(input) - 1] = '\0';
  return input;
};

void utils_get_path(char *cmd) {
  int fd[2];
  int fd_pipe = pipe(fd);

  char buffer[BUFFER_SIZE];
  char path[256] = "/usr/bin/";
  strcat(path, cmd);

  pid_t cpid = fork();

  if (cpid == 0) {
    dup2(fd[1], STDOUT_FILENO);
    char *args[] = {"which", cmd, NULL};
    execvp("which", args);
    perror("execvp");
    exit(1);
  } else {
    int status;
    waitpid(cpid, &status, 0);
    size_t size = read(fd[0], buffer, BUFFER_SIZE);
    buffer[size - 1] = '\0';

    close(fd[0]);
    close(fd[1]);

    if (size != 0) {
      printf("%s is in %s\n", cmd, buffer);
      return;
    }
    printf("%s: not found\n", cmd);

    return;
  };
  return;
};

char *utils_get_command(char *input) {
  size_t size = strlen(input);

  char *cmd = (char *)malloc((30 + 1) * sizeof(char));

  int char_counter = 0;
  if (cmd == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  for (int i = 0; i < size; ++i) {
    if (input[i] == '"' || input[i] == '\'')
      continue;

    if (isspace(input[i]) == 0)
      cmd[char_counter++] = input[i];
    else
      return cmd;
  };

  return cmd;
};
void utils_execute_program(char *input) {

  char *cmd = utils_get_command(input);
  if (strlen(cmd) == 0) {
    return;
  };

  args_t *args = calloc(1, sizeof(args_t));
  args = args_parse_arguments(input);

  char buffer[BUFFER_SIZE];

  int fd[2];

  int fd_pipe = pipe(fd);
  pid_t cpid = fork();

  if (cpid == -1) {
    perror("fork()");
    return;
  };

  if (cpid == 0) {
    dup2(fd[1], STDOUT_FILENO);
    execvp(cmd, args->argv);
    printf("%s: command not found\n", cmd);
  } else {
    int status;
    waitpid(cpid, &status, 0);
    size_t size = read(fd[0], buffer, BUFFER_SIZE);
    buffer[size] = '\0';
    close(fd[0]);
    close(fd[1]);
    if (args->has_operator) {
      printf("here");
      utils_redirect_stdout(buffer, args);
      return;
    }

    printf("here1");
    //   printf("%s", buffer);
  };
};

void utils_redirect_stdout(const char *buffer, const args_t *args) {
  // printf("%s\n", buffer);
  printf("------%s\n", args->argv[args->argc]);
};
