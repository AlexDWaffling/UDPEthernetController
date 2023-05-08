/**
 * @file UDPNetWork.h
 * @author NhanNguyenTrong
 * @brief
 * @version 0.0.1
 * @date 2023/08/05
 *
 *
 */

#ifndef UDPNetWork_H
#define UDPNetWork_H

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

class UDPSocket
{
public:
    UDPSocket();
    ~UDPSocket();

    void SendTo(const std::string &address, unsigned short port, const void *buffer, int len);

    void Send2To(sockaddr_in &address, const char *buffer, int len);

    void Bind(const std::string &address, unsigned short port);

    void Close(int socket);

    unsigned long Connect(const std::string &address, unsigned short port);

    std::vector<unsigned char> VectorConvData(int dataConv);

    sockaddr_in RecvFrom(char *buffer, int len);

private:
    int sock;
};
#endif