cmake_minimum_required(VERSION 3.5)

project(VehicleSimulator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

# GENERATED FILES FROM CENTRAL UNIT
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf/Client.grpc.pb.cc")
add_library(grpc_lib STATIC ${hw_grpc_srcs})
target_link_libraries(grpc_lib grpc++d)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../CentralUnit/CMake/build/grpc/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../CentralUnit/CMake/build/remote_control_vehicle/Interfaces/Protobuf)

if(ANDROID)
    add_library(VehicleSimulator SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(VehicleSimulator
      main.cpp
      qml.qrc
    )
endif()

target_compile_definitions(VehicleSimulator
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(VehicleSimulator
  PRIVATE Qt5::Core Qt5::Quick)
