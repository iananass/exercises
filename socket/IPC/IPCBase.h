#ifndef IPCBASE_H
#define	IPCBASE_H

class IPCBase
{
public:
    IPCBase();
    virtual ~IPCBase();
    
    int Receive(void* buf, int buflen);
    int Send(const void* buf, int buflen);
    void Close();
protected:
    int m_socket;
    bool m_connected;
private:
    IPCBase(const IPCBase& orig);
    const IPCBase& operator=(const IPCBase&);

};

#endif	/* IPCBASE_H */

