cmake_minimum_required(VERSION 3.10)

project(IntelligentVehicle)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(Vehicle/Include)
add_subdirectory(Vehicle/Source)

add_library(source_objects_lib OBJECT ${SOURCES})

add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:source_objects_lib>
                               "main.cpp")
