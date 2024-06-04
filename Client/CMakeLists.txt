cmake_minimum_required(VERSION 3.22.0)
project(Client VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)


add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    Networking
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
    Networking
    ws2_32
)
