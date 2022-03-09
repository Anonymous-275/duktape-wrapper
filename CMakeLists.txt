cmake_minimum_required(VERSION 3.0)
project(duktape-wrapper)

set(CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME} STATIC
        src/duk_wrapper.cpp include/duk_wrapper.h
        include/duktape/src/duktape.c include/duktape/extras/console/duk_console.c
        )


add_executable(duk_wrapper_example src/example.cpp)
target_link_libraries(duk_wrapper_example duktape-wrapper)

include_directories(include)
include_directories(include/duktape/src)
target_include_directories(${PROJECT_NAME} PRIVATE "include/duktape/extras")

