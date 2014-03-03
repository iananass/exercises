#include "IPC/IPCClient.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#define SOCK_PATH "echo_socket"

int main(void)
{
    IPCClient client;
    char str[128];
    if (!client.Connect(SOCK_PATH))
        return 1;

    std::cout << "Connected" << std::endl;

    while (1) {
        std::cout << "$ ";
        std::string message;
        std::cin >> message;
        client.Send(message.c_str(), message.size());
        int bytes_read = client.Receive(str, sizeof (str));
        if (bytes_read <= 0)
            return 1;
        std::cout << "    > '";
        for (int i = 0; i < bytes_read; ++i)
            std::cout << str[i];
        std::cout << "'" << std::endl;
        }
    return 0;
}