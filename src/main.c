#include "../include/utils.h"

#include "../include/builtin.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 500

int main(void) {

  char *input;
  do {
    char *buffer = malloc(sizeof(char *) * SIZE);
    if (getcwd(buffer, SIZE) == NULL)
      printf("error: Could not get path");

    printf("\n\n%s $ ", buffer);
    input = utils_get_input();

    if (builtin_check(input)) {
      continue;
    };
    utils_execute_program(input);
    free(buffer);
    free(input);
  } while (true);
  return 0;
};
