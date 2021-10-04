cmake_minimum_required(VERSION 3.17)
project(monotonic_time_lib C)

add_subdirectory(examples)

set(CMAKE_C_STANDARD 99)

set(deps ../deps/)
set(platform platform/)

if (WIN32)
    file(GLOB_RECURSE platform_src FOLLOW_SYMLINKS
        "${platform}/windows/*.c"
        )

    set(OS_WINDOWS 1)
endif()



file(GLOB_RECURSE deps_src FOLLOW_SYMLINKS
        "${deps}*/src/lib/*.c"
        )

file(GLOB_RECURSE lib_src FOLLOW_SYMLINKS
        "lib/*.c"
        )

add_library(monotonic_time_lib
    ${deps_src}
    ${lib_src}
    ${platform_src}
)

target_include_directories(monotonic_time_lib PUBLIC include)

if (WIN32)
    target_compile_definitions(monotonic_time_lib PRIVATE TORNADO_OS_WINDOWS)
    file(GLOB_RECURSE platform_src FOLLOW_SYMLINKS
        "${platform}/windows/*.c"
        )

    set(OS_WINDOWS 1)
else()
    file(GLOB_RECURSE platform_src FOLLOW_SYMLINKS
            "${platform}/posix/*.c"
            )


endif()


if (OS_WINDOWS)
target_link_libraries(monotonic_time_lib)
else()
target_link_libraries(monotonic_time_lib m)
endif()
