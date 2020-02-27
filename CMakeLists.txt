cmake_minimum_required(VERSION 3.15)

project(RemoteControlVehicle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system")

#set(LIBRARY_OUTPUT_PATH build/)
#set(BINARY_OUTPUT_PATH build/)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

include(External_GTest.cmake)
include(FetchContent)

if(GRPC_AS_SUBMODULE)

  # One way to build a projects that uses gRPC is to just include the
  # entire gRPC project tree via "add_subdirectory".
  # This approach is very simple to use, but the are some potential
  # disadvantages:
  # * it includes gRPC's CMakeLists.txt directly into your build script
  #   without and that can make gRPC's internal setting interfere with your
  #   own build.
  # * depending on what's installed on your system, the contents of submodules
  #   in gRPC's third_party/* might need to be available (and there might be
  #   additional prerequisites required to build them). Consider using
  #   the gRPC_*_PROVIDER options to fine-tune the expected behavior.
  #
  # A more robust approach to add dependency on gRPC is using
  # cmake's ExternalProject_Add (see cmake_externalproject/CMakeLists.txt).
  
  # Include the gRPC's cmake build (normally grpc source code would live
  # in a git submodule called "third_party/grpc", but this example lives in
  # the same repository as gRPC sources, so we just look a few directories up)
  add_subdirectory(../../.. ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)
  message(STATUS "Using gRPC via add_subdirectory.")

  # After using add_subdirectory, we can now use the grpc targets directly from
  # this build.
  set(_PROTOBUF_LIBPROTOBUF libprotobuf)
  if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
  else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
  endif()
  set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
  if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
  else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
  endif()
elseif(GRPC_FETCHCONTENT)
  # Another way is to use CMake's FetchContent module to clone gRPC at
  # configure time. This makes gRPC's source code available to your project,
  # similar to a git submodule.
  message(STATUS "Using gRPC via add_subdirectory (FetchContent).")
  include(FetchContent)
  FetchContent_Declare(
    grpc
    GIT_REPOSITORY https://github.com/grpc/grpc.git
    # when using gRPC, you will actually set this to an existing tag, such as
    # v1.25.0, v1.26.0 etc..
    # For the purpose of testing, we override the tag used to the commit
    # that's currently under test.
    GIT_TAG        vGRPC_TAG_VERSION_OF_YOUR_CHOICE)
  FetchContent_MakeAvailable(grpc)

  # Since FetchContent uses add_subdirectory under the hood, we can use
  # the grpc targets directly from this build.
  set(_PROTOBUF_LIBPROTOBUF libprotobuf)
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
  set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
  if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
  else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
  endif()
else()

  # This branch assumes that gRPC and all its dependencies are already installed
  # on this system, so they can be located by find_package().

  # Find Protobuf installation
  # Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
  set(protobuf_MODULE_COMPATIBLE TRUE)
  find_package(Protobuf CONFIG REQUIRED)
  message(STATUS "Using protobuf ${protobuf_VERSION}")

  set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
  if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
  else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
  endif()

  # Find gRPC installation
  # Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
  find_package(gRPC CONFIG REQUIRED)
  message(STATUS "Using gRPC ${gRPC_VERSION}")

  set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
  if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
  else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
  endif()
endif()

# GENERATED
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
add_library(grpc_lib STATIC ${hw_grpc_srcs} ${hw_grpc_hdrs})
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
add_dependencies(source_objects_lib commands)
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
