cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)


project(task31)

include_directories(.)
include_directories(src)

add_executable(task31 src/task1.c)

project(task32)

include_directories(.)
include_directories(src)

add_executable(task32 src/task2.c)
