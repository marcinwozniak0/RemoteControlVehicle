set(PROTO_FILES ControlerCommandToRun.proto
                EmptyAcknowledge.proto
                Deactivate.proto
                UserCommandToRun.proto
                UserCommandToStart.proto
                UserCommandToStop.proto
                InitCommands.proto)
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${PROTO_FILES})
add_library(commands STATIC ${ProtoSources})
target_link_libraries(commands ${PROTOBUF_LIBRARY})
