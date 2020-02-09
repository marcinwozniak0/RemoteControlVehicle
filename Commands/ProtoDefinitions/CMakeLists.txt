set(PROTO_FILES ControlerCommandToRun.proto
                Deactivate.proto
                UserCommandToRun.proto
                UserCommandToStart.proto
                UserCommandToStop.proto)
set(PROTO_FILES_GRPC Client.proto)
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${PROTO_FILES})
add_library(commands STATIC ${ProtoSources} ${ProtoHeaders})
target_link_libraries(commands ${PROTOBUF_LIBRARY})