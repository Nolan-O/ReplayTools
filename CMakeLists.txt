cmake_minimum_required(VERSION 2.8.4)

project(rpts)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCES 
    "main.cpp"
    "simpleopt.h"
    "data.cpp"
    "data.h"  
    "error.h"
    "error.cpp"
    "interface.cpp"
    "interface.h"
    "options.h"
    "options.cpp"
    )

add_executable(rpts ${SOURCES})
SET_TARGET_PROPERTIES(rpts PROPERTIES LINKER_LANGUAGE C)
find_library(LIB_CURSES ncurses)
target_link_libraries(rpts ${LIB_CURSES})
