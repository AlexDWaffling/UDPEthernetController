// // C++ UDP Transmitter

#include "../UDPNetWork.h"
#include "../UDPNetWork.cpp"
#include "../ServoController.h"
#include "../ServoController.cpp"
#include "iostream"
#include <string>
#include <locale>
#include <codecvt>
#include <bitset>
#include <vector>
#include <algorithm>

bool setState = false;
int main()
{
    std::string IP_L = "192.168.0.2";
    std::string IP_R = "192.168.0.7";
    std::string HOST_IP = "192.168.0.10";

    int MOTOR_PORT = 3001;
    int PORT = 3000;
    try
    {
        UDPSocket Socket;
        ServoController controller;
        std::vector<unsigned char> unprocessdata = {};
        std::string request = "\b";
        char buffer[100];
        Socket.Bind(HOST_IP, PORT);

        while (1)
        {
            //   std::cout << "Enter data to transmit : " << std::endl;
            //   std::getline(std::cin, data);
            sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
            std::string request(buffer);
            std::cout << "Processing - " << request << std::endl;
            for (int i = 0; i < 110; i += 10)
            {
                std::cout << "| " << i << "% |" << std::endl;
            }
            std::cout << "Done - " << request << std::endl;

            if (request == "enable")
            {
                // unprocessdata = {0xAA, 0x04, 0x01, 0x00, 0x2A, 0x01};
                // setState = true;
                controller.FAS_ServoEnable(IP_L, MOTOR_PORT, true);
            }
            else if (request == "disable")
            {
                //     unprocessdata = {0xAA, 0x04, 0x01, 0x00, 0x2A, 0x00};
                //     setState = true;
                controller.FAS_ServoEnable(IP_L, MOTOR_PORT, false);
            }
            else if (request == "run")
            {
                //     // unprocessdata = {0xAA, 0x08, 0x02, 0x00, 0x37, 0x70, 0x11, 0x01, 0x00, 0x01};
                //     // unprocessdata = {0xAA, 0x08, 0x02, 0x00, 0x37, 112, 17, 1, 0, 1};
                //     unprocessdata = {0xAA, 0x08, 0x02, 0x00, 0x37};
                //     std::vector<unsigned char> speed_pps = Socket.VectorConvData(70000);
                //     unprocessdata.insert(unprocessdata.end(), speed_pps.begin(), speed_pps.end());
                //     unprocessdata.push_back(1);
                //     setState = true;
                controller.FAS_MoveVelocity(IP_L, MOTOR_PORT, 10000, false);
            }
            else if (request == "stop")
            {
                //     unprocessdata = {0xAA, 0x03, 0x02, 0x00, 0x31};
                //     setState = true;
                controller.FAS_MoveStop(IP_L, MOTOR_PORT);
            }
            else if (request == "pos")
            {
                //     unprocessdata = {0xAA, 0x03, 0x02, 0x00, 0x53};
                //     setState = true;
                controller.FAS_GetActualPos(IP_L, MOTOR_PORT);
            }

            // /* Process Data */
            // auto size = unprocessdata.size();
            // unsigned char bytes[unprocessdata.size()];
            // std::copy(unprocessdata.begin(), unprocessdata.end(), bytes);

            // for (auto b : unprocessdata){
            //     std::cout << std::hex << (int)b << ' ';
            //     std::cout << std::endl;
            // }

            // if (setState == true)
            // {
            //     Socket.SendTo(IP_L, MOTOR_PORT, bytes, sizeof(bytes));
            //     // Socket.SendTo(IP_R, MOTOR_PORT, bytes, sizeof(bytes));
            //     setState = false;
            // }
            // Socket.Connect(IP_L, MOTOR_PORT);
        }
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what();
    }
}
