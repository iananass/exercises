#include "IPCServer.h"
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

IPCServer::IPCServer()
: m_listenSocketAlive(false)
{
}

IPCServer::~IPCServer()
{
    Close();
    StopBinding();
}

bool IPCServer::BindAndListen(const char* path)
{
    if (m_listenSocketAlive)
        return false;
    int len;
    struct sockaddr_un local;

    if ((m_listenSocket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return false;
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, path);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof (local.sun_family);
    if (bind(m_listenSocket, (struct sockaddr *) &local, len) == -1) {
        perror("bind");
        return false;
    }

    if (listen(m_listenSocket, 1) == -1) {
        perror("listen");
        return false;
    }
    m_listenSocketAlive = true;
    return true;
}

bool IPCServer::Accept()
{
    if (m_connected)
        return false;
    struct sockaddr_un remote;
    unsigned int t = sizeof (remote);
    if ((m_socket = accept(m_listenSocket, (struct sockaddr *) &remote, &t)) == -1) {
        return false;
    }
    m_connected = true;
    return true;
}

void IPCServer::StopBinding()
{
    if (m_listenSocketAlive) {
        m_listenSocketAlive = false;
        close(m_listenSocket);
    }
}

