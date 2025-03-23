#include <cstdlib>
#include <gtest/gtest.h>

extern "C" {
#include "../include/parser.h"
}

// Test cases
TEST(ParserTest, GetArgs) {
  const char *input = "cd arg1 arg2 arg3";

  Args *args = get_args((char *)input);

  // Check the number of arguments
  EXPECT_EQ(args->size, 3);

  // Check the individual arguments
  EXPECT_STREQ(args->data[0], "arg1");
  EXPECT_STREQ(args->data[1], "arg2");
  EXPECT_STREQ(args->data[2], "arg3");

  // Free allocated memory
  for (int i = 0; i < args->size; i++) {
    free(args->data[i]);
  }
  free(args->data);
};

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
