#ifndef IPCCLIENT_H
#define	IPCCLIENT_H

#include "IPCBase.h"

class IPCClient : public IPCBase
{
public:
    bool Connect(const char*);
};

#endif	/* IPCCLIENT_H */

