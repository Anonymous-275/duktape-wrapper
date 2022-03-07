cmake_minimum_required(VERSION 3.20)
project(duktape-wrapper)

set(CMAKE_CXX_STANDARD 17)

add_executable(duktape-wrapper main.cpp)

#target_link_libraries(duktape ${DUKTAPE_LIBRARY})
