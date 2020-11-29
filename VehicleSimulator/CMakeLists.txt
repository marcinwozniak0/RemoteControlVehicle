cmake_minimum_required(VERSION 3.5)

project(VehicleSimulator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts\
                                        -fPIC\
                                        -pthread\
                                        -g")

include(${CMAKE_CURRENT_SOURCE_DIR}/../CentralUnit/External_GTest.cmake)

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DQT_NO_VERSION_TAGGING)
find_package(Qt5 CONFIG COMPONENTS REQUIRED Core
                                            Widgets
                                            Quick
                                            Gui)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

# PROTOBUF
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf REQUIRED)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

# GRPC
find_package(gRPC REQUIRED)
set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
set(GENERATED_LIBS ${_GRPC_GRPCPP_UNSECURE} ${_PROTOBUF_LIBPROTOBUF})
message(STATUS "Using gRPC ${gRPC_VERSION}")

# GRPC GENERATED
get_filename_component(hw_proto "../Interfaces/Protobuf/Client.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf/Client.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf/Client.grpc.pb.h")

add_custom_command(
      OUTPUT "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out=generate_mock_code=true:"${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Interfaces/Protobuf ${CMAKE_CURRENT_BINARY_DIR}/Interfaces/Protobuf)

# GENERATED LIB
add_library(grpc_lib STATIC ${hw_grpc_srcs})
target_link_libraries(grpc_lib grpc++d)

# GENERATED INCLUDE FILES
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CMake/build/grpc/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CMake/build/vehicle_simulator/Interfaces/Protobuf)

# FILES FOR QT AUTOMOC
add_subdirectory(RentalOffice/Include)

# SRC
include_directories(RentalOffice/Include)
add_subdirectory(RentalOffice/Source)

# TEST
include_directories(RentalOffice/Test/Mock)
add_subdirectory(RentalOffice/Test/Source)

# SRC LIB
add_library(source_objects_lib OBJECT ${SOURCES}
                                      CommandReceiver.cpp
                                      GrpcCommandSender.cpp)

# BIN
add_executable(vehicle_simulator $<TARGET_OBJECTS:source_objects_lib>
                                 $<TARGET_OBJECTS:grpc_lib>
                                 ${FILES_FOR_QT_AUTOMOC}
                                 main.qml
                                 qml.qrc
                                 main.cpp)

target_compile_definitions(vehicle_simulator
                           PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(vehicle_simulator commands
                                        ${GENERATED_LIBS}
                                        Qt5::Core
                                        Qt5::Quick
                                        Qt5::Widgets)

# BIN UT
set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      $<TARGET_OBJECTS:grpc_lib>
                      ${TEST_FILES}
                      "MainTest.cpp")

add_executable(vehicle_simulator_ut ${TEST_BINARY_FILES})

target_link_libraries(vehicle_simulator_ut ${GTEST_LIBRARY}
                                           ${GMOCK_LIBRARY}
                                           ${GENERATED_LIBS}
                                           commands)
