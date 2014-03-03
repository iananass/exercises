#include "IPC/IPCServer.h"
#include <iostream>

#define SOCK_PATH "echo_socket"

int main(void)
{
    IPCServer server;
    server.BindAndListen(SOCK_PATH);

    while (1) {
        std::cout << "Waiting for a new connection." << std::endl;
        if (!server.Accept()) {
            perror("accept causes");
            exit(3);
        }
        int bytes_read;
        char str[128];
        while (1) {
            bytes_read = server.Receive(str, sizeof (str));
            if (bytes_read <= 0) {
                server.Close();
                break;
            }
            std::cout << "    > '";
            for (int i = 0; i < bytes_read; ++i)
                std::cout << str[i];
            std::cout << "'" << std::endl;
            server.Send(str, bytes_read);
        }
    }

    return 0;
}