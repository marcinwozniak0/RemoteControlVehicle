cmake_minimum_required(VERSION 3.5)

project(VehicleSimulator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts \
                                        -pthread \
                                        -g")

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)


set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
set(GENERATED_LIBS ${_GRPC_GRPCPP_UNSECURE} ${_PROTOBUF_LIBPROTOBUF})


# GENERATED FILES FROM CENTRAL UNIT
set(hw_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/../CentralUnit/CMake/build/remote_control_vehicle/Interfaces/Protobuf/Client.grpc.pb.cc")
add_library(grpc_lib STATIC ${hw_grpc_srcs})
target_link_libraries(grpc_lib grpc++d)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../CentralUnit/CMake/build/grpc/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../CentralUnit/CMake/build/remote_control_vehicle/Interfaces/Protobuf)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces/Protobuf ${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf)

if(ANDROID)
    add_library(VehicleSimulator SHARED
      $<TARGET_OBJECTS:grpc_lib>
      main.cpp
      qml.qrc
      commandreceiver.cpp
    )
else()
    add_executable(VehicleSimulator
      $<TARGET_OBJECTS:grpc_lib>
      main.cpp
      qml.qrc
      commandreceiver.cpp
    )
endif()



target_compile_definitions(VehicleSimulator
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(VehicleSimulator  ${GENERATED_LIBS}
    commands
   Qt5::Core Qt5::Quick)
