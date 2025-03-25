#include <cstdlib>
#include "gtest/gtest.h"

extern "C" {
#include "../include/parser.h"
}

// Test cases
TEST(ParserTest, GetArgs) {
  const char *input = "ls -alps";

  char *mutable_input = const_cast<char*>(input);
  Args *args = get_args(mutable_input);

  // Check the number of arguments
  EXPECT_EQ(args->size, 1);

  // Check the individual arguments
  EXPECT_STREQ(args->data[0], "-alps");
  //EXPECT_STREQ(args->data[1], "args1");
 // EXPECT_STREQ(args->data[2], "args2");

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
