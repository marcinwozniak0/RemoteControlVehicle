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
find_package(Protobuf REQUIRED)
find_program(Valgrind REQUIRED)

# GENERATED
include_directories(${CMAKE_BINARY_DIR}/Messages)
add_subdirectory(Messages)

# SRC
include_directories(Vehicle/Include)
include_directories(Router/Include)
include_directories(VehicleEquipment/Include)
include_directories(VehicleSystems/Include)
add_subdirectory(Vehicle/Source)
add_subdirectory(Router/Source)
add_subdirectory(VehicleEquipment/Source)
add_subdirectory(VehicleSystems/Source)

# TEST
include_directories(VehicleSystems/Test/Mock)
include_directories(VehicleSystems/Test/Include)
include_directories(VehicleEquipment/Test/Mock)
include_directories(VehicleEquipment/Test/Include)
include_directories(Vehicle/Test/Mock)
include_directories(Vehicle/Test/Include)
include_directories(Router/Test/Mock)
include_directories(Router/Test/Include)
add_subdirectory(VehicleSystems/Test)
add_subdirectory(VehicleEquipment/Test)
add_subdirectory(Vehicle/Test)
add_subdirectory(Router/Test)

# SRC LIB
add_library(source_objects_lib OBJECT ${SOURCES})

# BIN
add_executable(intelligent_vehicle $<TARGET_OBJECTS:source_objects_lib> "main.cpp")
target_link_libraries(intelligent_vehicle messages)


# UT
set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      ${TEST_FILES}
                      ${MAIN_TEST})
add_executable(intelligent_vehicle_ut ${TEST_BINARY_FILES})
target_link_libraries(intelligent_vehicle_ut ${GTEST_MAIN_LIBRARY}
                                          ${GTEST_LIBRARY}
                                          ${GMOCK_MAIN_LIBRARY}
                                          ${GMOCK_LIBRARY}
                                          messages)
# DEPENDENCIES
add_dependencies(source_objects_lib messages)
add_dependencies(messages googletest)

# Valgrind
target_link_libraries(intelligent_vehicle_ut LINK_PUBLIC)
add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck
                                                 --leak-check=yes
                                                 --show-reachable=yes
                                                 --num-callers=20
                                                 --track-fds=no
                                                 $<TARGET_FILE:intelligent_vehicle_ut>)
