/**
 * @file ControlMotorCommand.h
 * @author NhanNguyenTrong
 * @brief
 * @version 0.0.1
 * @date 2023/08/05
 *
 *
 */
#include <iostream>

#ifndef ControlMotorCommand_H
#define ControlMotorCommand_H

#define WHEEL_NUM 2
#define LEFT 0
#define RIGHT 1

#define LINEAR 0
#define ANGULAR 1
#define CCW 0
#define CW 1

#define AGV_Ezi_LIMIT_MAX_VELOCITY 500000 // PPS
#define AGV_Ezi_LIMIT_MIN_VELOCITY 0      // PPS

#define pi 3.14

class ControlMotorCommand
{
public:
    ControlMotorCommand();
    ~ControlMotorCommand();

    bool Init();

    bool ReadEncoder(int32_t &left_value, int32_t &right_value);

    bool WriteVelocity(int32_t left_value, int32_t right_value);

    bool ControlMotor(const float wheel_radius, const float wheel_separation, float *value);

    int constrain(int value, int maxVal, int minVal);

private:
    int port = 3001;
    std::string ip_left_motor = "192.168.0.2";
    std::string ip_right_motor = "192.168.0.7";
    bool flag_run_s1v1;
    bool flag_run_s1v2;
    bool flag_stop;
};
#endif