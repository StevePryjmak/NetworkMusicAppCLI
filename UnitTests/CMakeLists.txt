cmake_minimum_required(VERSION 3.22.0)
project(UnitTests VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)


add_executable(SongUnitTest SongsUnitTest/SongUnitTest.cpp)

target_include_directories(SongUnitTest
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/Networking
)

target_link_libraries(SongUnitTest
    PRIVATE 
    gtest_main
    Networking
)


enable_testing()

add_executable(PlaylistTest SongsUnitTest/PlaylistUnitTest.cpp)

target_include_directories(PlaylistTest
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/Networking
)

target_link_libraries(PlaylistTest
    PRIVATE 
    gtest_main
    Networking
)

add_executable(DatabaseTest DatabaseTest/DatabaseTest.cpp)

target_include_directories(DatabaseTest
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/Networking
)

target_link_libraries(DatabaseTest
    PRIVATE 
    gtest_main
    Networking
)