cmake_minimum_required(VERSION 3.12)

project(Server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(../External_GTest.cmake)
find_package(Protobuf REQUIRED)
find_program(Valgrind REQUIRED)

# GENERATED
include_directories(${CMAKE_BINARY_DIR}/Commands/ProtoDefinitions)
add_subdirectory(Commands/ProtoDefinitions)

# BIN
add_executable(server "main.cpp")
target_link_libraries(server commands)

# UT
set(TEST_BINARY_FILES ${TEST_FILES}
                      "MainTest.cpp")
add_executable(server_ut ${TEST_BINARY_FILES})
target_link_libraries(server_ut ${GTEST_MAIN_LIBRARY}
                                ${GTEST_LIBRARY}
                                ${GMOCK_MAIN_LIBRARY}
                                ${GMOCK_LIBRARY}
                                commands)

# Valgrind
find_program(VALGRIND "valgrind")
if(VALGRIND)
target_link_libraries(server_ut LINK_PUBLIC)
add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck
                                                 --leak-check=yes
                                                 --show-reachable=yes
                                                 --num-callers=20
                                                 --track-fds=no
                                                 --track-origins=yes
                                                 --error-exitcode=1
                                                 $<TARGET_FILE:server_ut>)
endif()
