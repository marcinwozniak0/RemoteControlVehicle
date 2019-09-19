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

include(External_GTest.cmake)
find_package(nlohmann_json 3.2.0 REQUIRED)

# SRC
include_directories(Vehicle/Include)
include_directories(Router/Include)
include_directories(VehicleEquipment/Include)
include_directories(VehicleConfiguration/Include)
add_subdirectory(Vehicle/Source)
add_subdirectory(Router/Source)
add_subdirectory(VehicleEquipment/Source)

# TEST
include_directories(VehicleEquipment/Test)
include_directories(Vehicle/Test)
include_directories(Router/Test)
add_subdirectory(VehicleEquipment/Test)
add_subdirectory(Vehicle/Test)
add_subdirectory(Router/Test)

add_library(source_objects_lib OBJECT ${SOURCES})

add_executable(intelligent_Vehicle $<TARGET_OBJECTS:source_objects_lib>
                                   "main.cpp")

target_link_libraries(intelligent_Vehicle nlohmann_json::nlohmann_json)

set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      ${TEST_FILES}
                      ${MAIN_TEST})

add_executable(intelligent_Vehicle_UT ${TEST_BINARY_FILES})
target_link_libraries(intelligent_Vehicle_UT ${GTEST_MAIN_LIBRARY}
                                          ${GTEST_LIBRARY}
                                          ${GMOCK_MAIN_LIBRARY}
                                          ${GMOCK_LIBRARY}
                                          nlohmann_json::nlohmann_json)
find_program(VALGRIND "valgrind")
if(VALGRIND)
    target_link_libraries(intelligent_Vehicle_UT LINK_PUBLIC)
    add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck  --leak-check=yes
    --show-reachable=yes --num-callers=20 --track-fds=no
    $<TARGET_FILE:intelligent_Vehicle_UT>)
endif()
