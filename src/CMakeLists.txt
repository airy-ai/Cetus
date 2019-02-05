cmake_minimum_required(VERSION 3.10.2)
project(Cetus)

set(CMAKE_C_COMPILER "/usr/bin/clang")

add_compile_options(-std=c17 -g -Weverything -Wall -Wextra -Wpedantic -pedantic-errors -O2 -march=native -Wmissing-prototypes -Wstrict-prototypes -D_XOPEN_SOURCE=800)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Cetus main.c cJSON.c)
