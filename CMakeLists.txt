 
cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(server LANGUAGES CXX)
add_executable(server server.cpp utils.h utils.cpp )
target_link_libraries(server pthread)

project(client LANGUAGES CXX)
add_executable(client client.cpp utils.h utils.cpp )
target_link_libraries(client pthread)