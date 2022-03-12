cmake_minimum_required(VERSION 3.17)
project(monotonic_time_example C)


set(deps ../../deps/)
set(CMAKE_C_STANDARD 99)

if (WIN32)
    file(GLOB_RECURSE platform_src FOLLOW_SYMLINKS
        "${platform}/windows/*.c"
        )

    set(OS_WINDOWS 1)
endif()


add_executable(monotonic_time_example
    main.c
)

if (WIN32)
    target_compile_definitions(monotonic_time_example PRIVATE TORNADO_OS_WINDOWS)
    set(OS_WINDOWS 1)
endif()


target_include_directories(monotonic_time_example PRIVATE ${deps}/clog/src/include)
target_include_directories(monotonic_time_example PRIVATE ${deps}/tiny-libc/src/include)

if (OS_WINDOWS)
target_link_libraries(monotonic_time_example monotonic_time_lib)
else()
target_link_libraries(monotonic_time_example monotonic_time_lib m)
endif()
