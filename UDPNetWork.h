#include <system_error>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <iostream>
#include <cstddef>
#include <bitset>

class UDPSocket
{
public:
    UDPSocket()
    {
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock < 0)
            throw "Error opening socket";
    }
    ~UDPSocket()
    {
        close(sock);
    }

    void SendTo(const std::string &address, unsigned short port, const char *buffer, int len, int flags = 0)
    {
        sockaddr_in add;
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_addr(address.c_str());
        // add.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", address.c_str());
        add.sin_port = htons(port);
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<sockaddr *>(&add), sizeof(add));
        if (ret < 0)
            throw "sendto failed";
    }
    void SendTo(sockaddr_in &address, const char *buffer, int len, int flags = 0)
    {
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<sockaddr *>(&address), sizeof(address));
        if (ret < 0)
            throw "sendto failed";
    }
    sockaddr_in RecvFrom(char *buffer, int len, int flags = 0)
    {
        sockaddr_in from;
        socklen_t size = sizeof(from);
        int ret = recvfrom(sock, buffer, len, flags, reinterpret_cast<sockaddr *>(&from), &size);
        if (ret < 0)
            throw "recvfrom failed";

        // make the buffer zero terminated
        buffer[ret] = 0;
        return from;
    }
    void Bind(unsigned short port)
    {
        sockaddr_in add;
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = htonl(INADDR_ANY);
        add.sin_port = htons(port);

        int ret = bind(sock, reinterpret_cast<sockaddr *>(&add), sizeof(add));
        if (ret < 0)
            throw "Bind failed";
    }

    std::bitset<64> convToBuffFrame(uint8_t header, uint8_t length, uint8_t syncNo, uint8_t reserved, uint8_t frameType, uint8_t data)
    {
        uint8_t bufferFrame[8] = {header, length, syncNo, reserved, frameType, data};
        uint64_t tempBuff;
        for (auto it : bufferFrame)
        {
            tempBuff = (tempBuff << 8) + it;
        }
        return tempBuff;
    }

private:
    int sock;
};
