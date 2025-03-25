# Find GoogleTest
set(GTEST_ROOT "/usr")  # Arch installs gtest here
find_package(GTest REQUIRED)

# Add the test executable
add_executable(parser_test parser_test.cc)

# Link the test executable to the library and gtest
target_link_libraries(parser_test coralis_lib GTest::GTest GTest::Main pthread)

# Enable testing
enable_testing()
add_test(NAME parser_test COMMAND parser_test)
