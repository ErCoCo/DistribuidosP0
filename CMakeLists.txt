 
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

project(serverObjects LANGUAGES CXX)
add_executable(serverObjects server.cpp utils.h utils.cpp)
target_link_libraries(serverObjects pthread)

project(clientObjects LANGUAGES CXX)
add_executable(clientObjects clientPerson.cpp utils.h utils.cpp person.h)
target_link_libraries(clientObjects pthread)
