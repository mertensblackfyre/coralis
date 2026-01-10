#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


bool helper_has_args(char *input) {
  int count = 0;
  size_t size = strlen(input);
  for (int i = 0; i < size; ++i)
    if (input[i] == ' ')
      count++;

  return count == 0;
};

char *helper_backtrack_path(char *s, int count) {
  size_t len = strlen(s);
  for (int i = len; i > 0; --i) {
    if (s[i] == '/')
      count--;
    if (count > 0)
      s[i] = '\0';
  };
  return s;
};

int helper_count_substrings(char *s) {

  size_t size = strlen(s);
  int count = 0;

  while ((s = strstr(s, "../")) != NULL) {
    count++;
    memmove(s, s + 3, strlen(s + 3) + 1);
  };
  return count;
};

char *helper_trim_space(char *string) {
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
