#include "../include/parser.h"
#include "../include/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


#define SIZE 500

int main(void) {

  char *input;
  do {
    char *buffer = malloc(sizeof(char *) * SIZE);
    getcwd(buffer, SIZE);
    printf("\n\n%s $ ",buffer);
    input = get_input();
    if (isbuiltin(input)) {
      continue;
    };
    exe_program(input);
  } while (true);
  return 0;
};
