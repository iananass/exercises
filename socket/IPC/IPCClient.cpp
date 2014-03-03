#include "IPCClient.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

bool IPCClient::Connect(const char* path)
{
    if (m_connected)
        return false;

    if ((m_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return false;
    }
    m_connected = true;


    struct sockaddr_un remote;
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, path);
    int len = strlen(remote.sun_path) + sizeof (remote.sun_family);
    if (connect(m_socket, (struct sockaddr *) &remote, len) == -1) {
        perror("connect");
        return false;
    }
    return true;
}