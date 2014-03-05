CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (IPC)

SET(ServerSources 
    Server.cpp)

SET(ClientSources
    Client.cpp)

ADD_SUBDIRECTORY(IPC)

ADD_EXECUTABLE(Server ${ServerSources})
ADD_EXECUTABLE(Client ${ClientSources})

TARGET_LINK_LIBRARIES(Server IPClib)
TARGET_LINK_LIBRARIES(Client IPClib)