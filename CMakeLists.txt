cmake_minimum_required(VERSION 3.20)
project(duktape-wrapper)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)

#target_link_libraries(${PROJECT_NAME} ${DUKTAPE_LIBRARY})

target_include_directories(${PROJECT_NAME} PRIVATE "include")
