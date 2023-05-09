#include <iostream>
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
#include "ControlMotorCommand.h"
#include "ServoController.h"

ServoController controller;

ControlMotorCommand::ControlMotorCommand() {}
ControlMotorCommand::~ControlMotorCommand() {}

bool ControlMotorCommand::Init()
{
    controller.FAS_ServoEnable(ip_left_motor, port, true);
    controller.FAS_ServoEnable(ip_right_motor, port, true);

    controller.FAS_MoveStop(ip_left_motor, port);
    controller.FAS_MoveStop(ip_right_motor, port);

    controller.FAS_ClearPosition(ip_left_motor, port);
    controller.FAS_ClearPosition(ip_right_motor, port);

    return true;
}

bool ControlMotorCommand::ReadEncoder(int32_t &left_value, int32_t &right_value)
{
    left_value = controller.FAS_GetActualPos(ip_left_motor, port);
    right_value = controller.FAS_GetActualPos(ip_right_motor, port);
    return true;
}

bool ControlMotorCommand::WriteVelocity(int32_t left_value, int32_t right_value)
{
    return true;
}

bool ControlMotorCommand::ControlMotor(const float wheel_radius, const float wheel_separation, float *value)
{
    bool dxl_comm_result = false;
    uint8_t com_status = 0;

    float wheel_velocity_cmd[2];
    uint32_t wheel_pps_cmd[2];

    float lin_vel = value[LINEAR];
    float ang_vel = value[ANGULAR];

    wheel_velocity_cmd[LEFT] = lin_vel - (ang_vel * wheel_separation / 2);
    wheel_velocity_cmd[RIGHT] = lin_vel + (ang_vel * wheel_separation / 2);

    wheel_pps_cmd[LEFT] = constrain((abs(wheel_velocity_cmd[LEFT]) / (2 * pi * wheel_radius)) * 100000, AGV_Ezi_LIMIT_MIN_VELOCITY, AGV_Ezi_LIMIT_MAX_VELOCITY);
    wheel_pps_cmd[RIGHT] = constrain((abs(wheel_velocity_cmd[RIGHT]) / (2 * pi * wheel_radius)) * 100000, AGV_Ezi_LIMIT_MIN_VELOCITY, AGV_Ezi_LIMIT_MAX_VELOCITY);

    if (wheel_velocity_cmd[LEFT] == 0 && wheel_velocity_cmd[RIGHT] == 0)
    {
        controller.FAS_MoveVelocity(ip_left_motor, port, 0, false);
        controller.FAS_VelocityOverride(ip_left_motor, port, wheel_pps_cmd[LEFT]);
        controller.FAS_MoveVelocity(ip_right_motor, port, 0, false);
        controller.FAS_VelocityOverride(ip_right_motor, port, wheel_pps_cmd[RIGHT]);
    }
    else
    {
        /* Đã sửa từ 400000 -> 100000 */
        if (wheel_velocity_cmd[LEFT] > 0)
        {
            controller.FAS_MoveVelocity(ip_left_motor, port, 100000, false);
            controller.FAS_VelocityOverride(ip_left_motor, port, wheel_pps_cmd[LEFT]);
        }
        if (wheel_velocity_cmd[LEFT] < 0)
        {
            controller.FAS_MoveVelocity(ip_left_motor, port, 100000, true);
            controller.FAS_VelocityOverride(ip_left_motor, port, wheel_pps_cmd[LEFT]);
        }
        if (wheel_velocity_cmd[RIGHT] > 0)
        {
            controller.FAS_MoveVelocity(ip_right_motor, port, 100000, true);
            controller.FAS_VelocityOverride(ip_right_motor, port, wheel_pps_cmd[RIGHT]);
        }
        if (wheel_velocity_cmd[RIGHT] < 0)
        {
            controller.FAS_MoveVelocity(ip_right_motor, port, 100000, false);
            controller.FAS_VelocityOverride(ip_right_motor, port, wheel_pps_cmd[RIGHT]);
        }
    }
    dxl_comm_result = WriteVelocity((int64_t)wheel_velocity_cmd[LEFT], (int64_t)wheel_velocity_cmd[RIGHT]);
    if (dxl_comm_result == false)
        return false;
    return true;
}

int ControlMotorCommand::constrain(int value, int minVal, int maxVal)
{
    if (value < minVal)
    {
        return minVal;
    }
    else if (value > maxVal)
    {
        return maxVal;
    }
    else
    {
        return value;
    }
}