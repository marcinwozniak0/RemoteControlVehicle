cmake_minimum_required(VERSION 3.15)

project(RemoteControlVehicle)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(External_GTest.cmake)
include(FetchContent)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)


# GRPC GENERATED
get_filename_component(hw_proto "Commands/ProtoDefinitions/Client.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/Client.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/Client.grpc.pb.h")

add_custom_command(
      OUTPUT "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out=generate_mock_code=true:"${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

add_subdirectory(Commands/ProtoDefinitions)
include_directories(${CMAKE_BINARY_DIR}/Commands/ProtoDefinitions)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# GRPC INCLUDE FILES
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CMake/build/grpc/include/)

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

# GRPC GENERATED LIB
add_library(grpc_lib STATIC ${hw_grpc_srcs})
target_link_libraries(grpc_lib grpc++d)

# BIN
add_executable(remote_control_vehicle $<TARGET_OBJECTS:source_objects_lib> 
                                      $<TARGET_OBJECTS:grpc_lib>
                                      "main.cpp")
target_link_libraries(remote_control_vehicle
                     commands
                     ${_GRPC_GRPCPP_UNSECURE}
                     ${_PROTOBUF_LIBPROTOBUF})

# UT
set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      $<TARGET_OBJECTS:grpc_lib>
                      ${TEST_FILES}
                      "MainTest.cpp")
add_executable(remote_control_vehicle_ut ${TEST_BINARY_FILES})
target_link_libraries(remote_control_vehicle_ut ${GTEST_MAIN_LIBRARY}
                                                ${GTEST_LIBRARY}
                                                ${GMOCK_MAIN_LIBRARY}
                                                ${GMOCK_LIBRARY}
                                                commands                             
                                                ${_GRPC_GRPCPP_UNSECURE}
                                                ${_PROTOBUF_LIBPROTOBUF})

# DEPENDENCIES
add_dependencies(grpc_lib commands)
add_dependencies(source_objects_lib grpc_lib)
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
                                                 --gen-suppressions=all
                                                 --suppressions=../../../valgrind.supp
                                                 $<TARGET_FILE:remote_control_vehicle_ut>)
endif()