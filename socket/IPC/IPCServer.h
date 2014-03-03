#ifndef IPCSERVER_H
#define	IPCSERVER_H

#include "IPCBase.h"

class IPCServer : public IPCBase
{
public:
    IPCServer();
    ~IPCServer();
    bool BindAndListen(const char*);
    bool Accept();
    void StopBinding();
private:
    int m_listenSocket;
    bool m_listenSocketAlive;
};

#endif	/* IPCSERVER_H */

