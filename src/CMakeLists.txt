# Create a library from the source files
add_library(coralis_lib
    builtin.c
    parser.c
    utils.c
)

# If you have a main.c, create an executable for it
add_executable(coralis main.c)

# Link the library to the main executable
target_link_libraries(coralis coralis_lib)
