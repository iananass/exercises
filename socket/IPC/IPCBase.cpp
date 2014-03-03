#include "IPCBase.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

IPCBase::IPCBase()
: m_connected(false)
{
}

IPCBase::~IPCBase()
{
    Close();
}

int IPCBase::Receive(void* buf, int buflen)
{
    if (!m_connected)
        return -1;
    return recv(m_socket, buf, buflen, 0);
}

int IPCBase::Send(const void* buf, int buflen)
{
    if (!m_connected)
        return -1;
    return send(m_socket, buf, buflen, 0);
}

void IPCBase::Close()
{
    if (m_connected) {
        m_connected = false;
        close(m_socket);
    }
}
