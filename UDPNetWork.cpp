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
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "UDPNetWork.h"

UDPSocket::UDPSocket()
{
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
        throw "Error opening socket";
}
UDPSocket::~UDPSocket()
{
    close(sock);
}

void UDPSocket::SendTo(const std::string &address, unsigned short port, const void *buffer, int len)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(address.c_str());
    // add.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", address.c_str());
    add.sin_port = htons(port);
    int ret = sendto(sock, buffer, len, 0, reinterpret_cast<sockaddr *>(&add), sizeof(add));
    std::cout << "Buffer: " << buffer << std::endl;
    if (ret < 0)
        throw "sendto failed";
}
void UDPSocket::Send2To(sockaddr_in &address, const char *buffer, int len)
{
    int ret = sendto(sock, buffer, len, 0, reinterpret_cast<sockaddr *>(&address), sizeof(address));
    if (ret < 0)
        throw "sendto failed";
}
sockaddr_in UDPSocket::RecvFrom(char *buffer, int len)
{
    sockaddr_in from;
    socklen_t size = sizeof(from);
    int ret = recvfrom(sock, buffer, len, 0, reinterpret_cast<sockaddr *>(&from), &size);
    if (ret < 0)
        throw "recvfrom failed";

    // make the buffer zero terminated
    buffer[ret] = 0;
    return from;
}
void UDPSocket::Bind(const std::string &address, unsigned short port)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(address.c_str());
    // add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_port = htons(port);

    int ret = bind(sock, reinterpret_cast<sockaddr *>(&add), sizeof(add));
    if (ret < 0)
        throw "Bind failed";
}
void UDPSocket::Close(int socket)
{
    close(sock);
}
unsigned long UDPSocket::Connect(const std::string &address, unsigned short port)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(address.c_str());
    // add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_port = htons(port);

    connect(sock, reinterpret_cast<sockaddr *>(&add), sizeof(add));
    unsigned char buffer[10] = {0};
    int valread = recv(sock, buffer, sizeof(buffer), 0);
    for (auto b : buffer)
    {
        std::cout << "Recv:" << std::hex << (int)b << ' ' << std::endl;
    }

    int dataLength = buffer[1] + 1;
    std::bitset<32> buffData[4];
    std::bitset<32> buff;
    unsigned long data;
    for (int i = 0; i < 4; i++)
    {
        buffData[i] = buffer[dataLength - i];
        std::cout << "binary " << i << ':' << buffData[i].to_string() << std::endl;
    }
    buff = buffData[0] << 24 | buffData[1] << 16 | buffData[2] << 8 | buffData[3] << 0;
    std::cout << "Buff " << buff.to_string() << std::endl;
    data = buff.to_ulong();
    std::cout << "Number: " << std::to_string(data) << std::endl;
    return data;
}
std::vector<unsigned char> UDPSocket::VectorConvData(int dataConv) // return type is struct demo
{
    std::vector<unsigned char> unprocessdata = {};
    for (int i = 0; i < 32; i += 8)
    {
        unprocessdata.push_back(dataConv >> i);
    }
    return unprocessdata;
}
