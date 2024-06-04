cmake_minimum_required(VERSION 3.22.0)
project(Networking VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.85.0 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp )
#file(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${Boost_INCLUDE_DIRS}
PRIVATE
    
    
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    ${Boost_LIBRARIES}
    ws2_32
    mswsock
# PRIVATE
#     ${Boost_LIBRARIES}
)




# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
