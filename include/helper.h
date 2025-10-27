#ifndef HELPER_H
#define HELPER_H

bool helper_has_args(const char *input);
int helper_count_substrings(char *s);
char *helper_backtrack_path(char *s, int count);
// char *helper_handle_str(Args *data);
char *helper_trim_space(char *string);
void helper_find_program();

#endif
