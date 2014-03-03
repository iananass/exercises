CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (IPC)

SET(ServerSources 
    IPC/IPCServer.cpp
    IPC/IPCBase.cpp
    Server.cpp)

SET(ClientSources
    IPC/IPCClient.cpp
    IPC/IPCBase.cpp
    Client.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

ADD_EXECUTABLE(Server ${ServerSources})
ADD_EXECUTABLE(Client ${ClientSources})