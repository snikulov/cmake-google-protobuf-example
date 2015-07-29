cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME test_proto)
project(${PROJECT_NAME})

find_package(Protobuf REQUIRED)

set(PROTO_FILES
    proto/msg.proto
    )

set(SRC_FILES
    src/main.cpp
    )

set(HDR_FILES
    )

PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HDR ${PROTO_FILES})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES} ${PROTO_SRC} ${PROTO_HDR} ${PROTO_FILES})
target_include_directories(${PROJECT_NAME}
   PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
   PUBLIC ${PROTOBUF_INCLUDE_DIRS}
   )
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})
