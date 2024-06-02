cmake_minimum_required(VERSION 3.22.0)
project(Client VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)



# include(FetchContent)

# FetchContent_Declare(
#     googletest
#     GIT_REPOSITORY https://github.com/google/googletest.git
#     GIT_TAG        main
# )
# FetchContent_MakeAvailable(googletest)


# set( )

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
#target_link_libraries(Tests PRIVATE gtest_main)



# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
