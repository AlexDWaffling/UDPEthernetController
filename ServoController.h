/**
 * @file ServoController.h
 * @author NhanNguyenTrong
 * @brief
 * @version 0.0.1
 * @date 2023/08/05
 *
 *
 */

#ifndef ServoController_H
#define ServoController_H

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

#define ServoEnable             0x2A
#define ServoAlarmReset         0x2B
#define MoveStop                0x31
#define EmergencyStop           0x32
#define MoveSingleAxisAbsPos    0x34
#define MoveVelocity            0x37
#define VelocityOverride        0x3A
#define GetActualPos            0x53

class ServoController
{
public:
    ServoController();
    ~ServoController();

    void FAS_ServoEnable(std::string ipAddr, int port, bool status);
    void FAS_ServoAlarmReset(std::string ipAddr, int port);
    unsigned long FAS_MoveStop(std::string ipAddr, int port);
    unsigned long FAS_EmergencyStop(std::string ipAddr, int port);
    unsigned long FAS_MoveSingleAxisAbsPos(std::string ipAddr, int port, int32_t posVal, uint32_t speed_pps);
    unsigned long FAS_MoveVelocity(std::string ipAddr, int port, uint32_t speed_pps, bool jog_dir);
    unsigned long FAS_GetActualPos(std::string ipAddr, int port);
    unsigned long FAS_VelocityOverride(std::string ipAddr, int port, uint32_t new_speed_pps);

private:
    unsigned char header = 0xAA;
    unsigned char reserved = 0x00;
    unsigned char length = 0x03;
    unsigned char syncNo = 0x00;
    unsigned char frameType = 0x00;
    int port = 3001;
    int port_host = 3000;
    std::string ip_left_motor = "192.168.0.2";
    std::string ip_right_motor = "192.168.0.7";
    std::string ip_host = "192.168.0.10";
};
#endif