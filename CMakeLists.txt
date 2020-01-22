cmake_minimum_required(VERSION 3.12)

project(RemoteControlVehicle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system")

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

include(External_GTest.cmake)
find_package(Protobuf REQUIRED)
find_program(Valgrind REQUIRED)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)
find_package(PkgConfig REQUIRED)

function(PROTOBUF_GENERATE_GRPC_CPP SRCS HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: PROTOBUF_GENERATE_GRPC_CPP() called without any proto files")
    return()
  endif()

  if(PROTOBUF_GENERATE_CPP_APPEND_PATH) # This variable is common for all types of output.
    # Create an include path for each file specified
    foreach(FIL ${ARGN})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component(ABS_PATH ${ABS_FIL} PATH)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  else()
    set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(DIR ${Protobuf_IMPORT_DIRS})
      get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  endif()

  set(${SRCS})
  set(${HDRS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.cc")
    list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.h")

    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.cc"
             "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.h"
      COMMAND  ${Protobuf_PROTOC_EXECUTABLE}
      ARGS --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
           --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
           ${_protobuf_include_path} ${ABS_FIL}
      DEPENDS ${ABS_FIL} ${Protobuf_PROTOC_EXECUTABLE}
      COMMENT "Running gRPC C++ protocol buffer compiler on ${FIL}"
      VERBATIM)
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()


# GENERATED
include_directories(${CMAKE_BINARY_DIR}/Commands/ProtoDefinitions)
add_subdirectory(Commands/ProtoDefinitions)

# SRC
include_directories(Vehicle/Include)
include_directories(Router/Include)
include_directories(VehicleEquipment/Include)
include_directories(VehicleSystems/Include)
include_directories(Commands/Builders/Include)
include_directories(Utilites/Include)
include_directories(Logger/Include)
add_subdirectory(Vehicle/Source)
add_subdirectory(Router/Source)
add_subdirectory(VehicleEquipment/Source)
add_subdirectory(VehicleSystems/Source)
add_subdirectory(Commands/Builders/Source)
add_subdirectory(Utilites/Source)
add_subdirectory(Logger/Source)

# TEST
include_directories(VehicleSystems/Test/Mock)
include_directories(VehicleSystems/Test/Include)
include_directories(VehicleEquipment/Test/Mock)
include_directories(VehicleEquipment/Test/Include)
include_directories(Vehicle/Test/Mock)
include_directories(Vehicle/Test/Include)
include_directories(Router/Test/Mock)
include_directories(Router/Test/Include)
include_directories(Commands/Builders/Test/Mock)
include_directories(Commands/Builders/Test/Include)
include_directories(SystemTest/Test/Include)
add_subdirectory(VehicleSystems/Test/Source)
add_subdirectory(VehicleEquipment/Test/Source)
add_subdirectory(Vehicle/Test/Source)
add_subdirectory(Router/Test/Source)
add_subdirectory(Commands/Builders/Test/Source)
add_subdirectory(SystemTest/Test/Source)
add_subdirectory(Utilites/Test/Source)

# SRC LIB
add_library(source_objects_lib OBJECT ${SOURCES})

# BIN
add_executable(remote_control_vehicle $<TARGET_OBJECTS:source_objects_lib> "main.cpp")
target_link_libraries(remote_control_vehicle commands)

# UT
set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      ${TEST_FILES}
                      "MainTest.cpp")
add_executable(remote_control_vehicle_ut ${TEST_BINARY_FILES})
target_link_libraries(remote_control_vehicle_ut ${GTEST_MAIN_LIBRARY}
                                                ${GTEST_LIBRARY}
                                                ${GMOCK_MAIN_LIBRARY}
                                                ${GMOCK_LIBRARY}
                                                commands)
# DEPENDENCIES
add_dependencies(source_objects_lib commands)
add_dependencies(commands googletest)


# Valgrind
find_program(VALGRIND "valgrind")
if(VALGRIND)
target_link_libraries(remote_control_vehicle_ut LINK_PUBLIC)
add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck
                                                 --leak-check=yes
                                                 --show-reachable=yes
                                                 --num-callers=20
                                                 --track-fds=no
                                                 --track-origins=yes
                                                 --error-exitcode=1
                                                 $<TARGET_FILE:remote_control_vehicle_ut>)
endif()
