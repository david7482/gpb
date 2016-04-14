cmake_minimum_required(VERSION 3.2)
project(gpb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(LIBPROTOBUF REQUIRED protobuf)
if(LIBPROTOBUF_FOUND)
    include_directories(${LIBPROTOBUF_INCLUDE_DIRS})
    link_directories(${LIBPROTOBUF_LIBRARY_DIRS})
endif()

execute_process(COMMAND protoc -I=../proto --cpp_out=../proto ../proto/test0.proto)

set(SOURCE_FILES main.cpp
        proto/test0.pb.h
        proto/test0.pb.cc
)

add_executable(gpb ${SOURCE_FILES})
target_link_libraries(gpb ${LIBPROTOBUF_LIBRARIES})