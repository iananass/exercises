cmake_minimum_required(VERSION 2.8)

project(IPClib)

set(SOURCE_LIB
    IPCClient.cpp
    IPCServer.cpp
    IPCBase.cpp)

add_library(IPClib STATIC ${SOURCE_LIB})