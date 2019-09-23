file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${PROTO_FILES})
add_library(messages STATIC ${ProtoSources} ${ProtoHeaders})
target_link_libraries(messages ${PROTOBUF_LIBRARY})
