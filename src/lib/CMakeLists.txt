cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS false)

# --- Detect CMake build type, compiler and operating system ---

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("detected debug build")
  set(isDebug TRUE)
else()
  message("detected release build")
  set(isDebug FALSE)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(COMPILER_NAME "clang")
  set(COMPILER_CLANG 1)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(COMPILER_NAME "gcc")
  set(COMPILER_GCC 1)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  set(COMPILER_NAME "msvc")
  set(COMPILER_MSVC 1)
endif()

message("detected compiler: '${CMAKE_C_COMPILER_ID}' (${COMPILER_NAME})")

set(useSanitizers false)

if(useSanitizers)
  message("using sanitizers")
  set(sanitizers "-fsanitize=address")
endif()

if(APPLE)
  message("MacOS detected!")
  set(OS_MACOS 1)
elseif(UNIX)
  message("Linux Detected!")
  set(OS_LINUX 1)
elseif(WIN32)
  message("Windows detected!")
  set(OS_WINDOWS 1)
endif()

# --- Library ---

file(GLOB lib_src FOLLOW_SYMLINKS "./*.c")
if(OS_WINDOWS)
  file(GLOB platform_src FOLLOW_SYMLINKS "../platform/windows/*.c")
else()
  file(GLOB platform_src FOLLOW_SYMLINKS "../platform/posix/*.c")
endif()

add_library(monotonic-time STATIC ${lib_src} ${platform_src})

if(OS_MACOS)
  target_compile_definitions(monotonic-time PRIVATE TORNADO_OS_MACOS)
elseif(OS_LINUX)
  target_compile_definitions(monotonic-time PRIVATE TORNADO_OS_LINUX)
elseif(OS_WINDOWS)
  target_compile_definitions(monotonic-time PRIVATE TORNADO_OS_WINDOWS)
endif()

if(isDebug)
  message("Setting definitions based on debug")
  target_compile_definitions(monotonic-time PRIVATE CONFIGURATION_DEBUG)
endif()

target_include_directories(monotonic-time PUBLIC ../include)

if(COMPILER_CLANG)
  target_compile_options(
    monotonic-time
    PRIVATE -Weverything
            -Werror
            -Wno-padded # the order of the fields in struct can matter (ABI)
            -Wno-declaration-after-statement # must be bug in clang? shows up
                                             # even if std=c99
            -Wno-unsafe-buffer-usage # unclear why it fails on clang-16
            -Wno-unknown-warning-option # support newer clang versions, e.g.
                                        # clang-16
            -Wno-disabled-macro-expansion # bug in emscripten compiler?
            ${sanitizers})
elseif(COMPILER_GCC)
  target_compile_options(
    monotonic-time
    PRIVATE -Wall
            -Wextra
            -Wpedantic
            -Werror
            -Wno-padded # the order of the fields in struct can matter (ABI)
            ${sanitizers})
elseif(COMPILER_MSVC)
  target_compile_options(
    monotonic-time
    PRIVATE /Wall
            /WX
            # /F 5000000 # stack size
            /wd4820 # bytes padding added after data member
            /wd4668 # bug in winioctl.h (is not defined as a preprocessor macro,
                    # replacing with '0' for '#if/#elif')
            /wd5045 # Compiler will insert Spectre mitigation for memory load if
                    # /Qspectre switch specified
            /wd4005 # Bug in ntstatus.h (macro redefinition)
  )
else()
  target_compile_options(monotonic-time PRIVATE -Wall)
endif()

target_link_libraries(monotonic-time PUBLIC clog)

if(useSanitizers)
  target_link_libraries(monotonic-time PRIVATE ${sanitizers})
endif()

if(NOT isDebug)
  message("optimize!")
  target_compile_options(monotonic-time PRIVATE -O3)
endif()
