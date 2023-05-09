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
#include "ServoController.h"
#include "UDPNetWork.h"

UDPSocket Socket;

ServoController::ServoController() {}
ServoController::~ServoController() {}

void ServoController::FAS_ServoEnable(std::string ipAddr, int port, bool status)
{
    /* Update Data */
    length = 0x04;
    frameType = ServoEnable;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    unprocessdata.push_back(static_cast<unsigned char>(status));
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}
void ServoController::FAS_ServoAlarmReset(std::string ipAddr, int port)
{
    /* Update Data */
    length = 0x03;
    frameType = ServoAlarmReset;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}
void ServoController::FAS_MoveStop(std::string ipAddr, int port)
{
    /* Update Data */
    length = 0x03;
    frameType = MoveStop;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}
void ServoController::FAS_EmergencyStop(std::string ipAddr, int port)
{
    /* Update Data */
    length = 0x03;
    frameType = EmergencyStop;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}
void ServoController::FAS_MoveSingleAxisAbsPos(std::string ipAddr, int port, int32_t posVal, uint32_t speed_pps)
{
    /* Update Data */
    length = 0x0B;
    frameType = MoveSingleAxisAbsPos;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    std::vector<unsigned char> pos = Socket.VectorConvData(posVal);
    unprocessdata.insert(unprocessdata.end(), pos.begin(), pos.end());
    std::vector<unsigned char> speed = Socket.VectorConvData(speed_pps);
    unprocessdata.insert(unprocessdata.end(), speed.begin(), speed.end());
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}
void ServoController::FAS_MoveVelocity(std::string ipAddr, int port, uint32_t speed_pps, bool jog_dir)
{
    /* Update Data */
    length = 0x08;
    frameType = MoveVelocity;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    std::vector<unsigned char> speed = Socket.VectorConvData(speed_pps);
    unprocessdata.insert(unprocessdata.end(), speed.begin(), speed.end());
    unprocessdata.push_back(static_cast<unsigned char>(jog_dir));
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}
unsigned long ServoController::FAS_GetActualPos(std::string ipAddr, int port)
{
    /* Update Data */
    length = 0x03;
    frameType = GetActualPos;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};

    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while (true)
    {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() > 100)
        {
            Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
            unsigned long data = Socket.Connect(ipAddr, port);
            // std::cout << "Number: " << std::to_string(data) << std::endl;
            begin = end;
            return data;
        }
    }
}
void ServoController::FAS_VelocityOverride(std::string ipAddr, int port, uint32_t new_speed_pps)
{
    /* Update Data */
    length = 0x07;
    frameType = VelocityOverride;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    std::vector<unsigned char> speed = Socket.VectorConvData(new_speed_pps);
    unprocessdata.insert(unprocessdata.end(), speed.begin(), speed.end());
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}

void ServoController::FAS_ClearPosition(std::string ipAddr, int port)
{
     /* Update Data */
    length = 0x03;
    frameType = ClearPosition;
    std::vector<unsigned char> unprocessdata = {header, length, syncNo, reserved, frameType};
    /* Process Data */
    auto size = unprocessdata.size();
    unsigned char bytes[unprocessdata.size()];
    std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

    Socket.SendTo(ipAddr, port, bytes, sizeof(bytes));
}