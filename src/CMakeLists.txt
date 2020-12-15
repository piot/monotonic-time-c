cmake_minimum_required(VERSION 3.17)
project(monotonic_time_example C)

set(CMAKE_C_STANDARD 99)

set(deps ../deps/)

include_directories(include)

file(GLOB_RECURSE deps_src FOLLOW_SYMLINKS
        "${deps}*/src/lib/*.c"
        )

file(GLOB_RECURSE lib_src FOLLOW_SYMLINKS
        "lib/*.c"
        )

add_executable(monotonic_time_example
    ${deps_src}
    ${lib_src}
    examples/main.c
)
target_link_libraries(monotonic_time_example m)
