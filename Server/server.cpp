// C++ UDP Transmitter

#include "../UDPNetWork.h"
#include "iostream"
#include <string> 
#include <locale> 
#include <codecvt> 
#include <bitset>

int main()
{
    std::string IP = "127.0.0.1";
    int PORT = 8886;
    try
    {
        UDPSocket Socket;
        std::string data = Socket.convToBuffFrame(0xAA, 0x10, 0x01, 0x00, 0x31, 0x01).to_string();
        std::string data2 = Socket.convToBuffFrame(0xAA, 0x10, 0x01, 0x00, 0x31, 0x01).to_string();
        std::string data3 = "Motor 1 has been stopped";
        std::string data4 = "Motor 2 has been stopped";
        std::string request = "\b";
        char buffer[100];
        int delay_time = 0;
        Socket.Bind(PORT);

        while (1)
        {
            //   std::cout << "Enter data to transmit : " << std::endl;
            //   std::getline(std::cin, data);
            sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
            std::string request(buffer);
            std::cout << "Processing - " << request << std::endl;
            for(int i = 0; i < 110; i+=10){
                std::cout << "| "<< i <<"% |" << std::endl;
            }
            std::cout << "Done - " << request << std::endl;
            if (request == "enable motor")
            {
                Socket.SendTo(IP, 8888, data.c_str(), data.size());
                Socket.SendTo(IP, 8889, data2.c_str(), data2.size());
            }
            if (request == "disable motor")
            {
                Socket.SendTo(IP, 8888, data3.c_str(), data.size());
                Socket.SendTo(IP, 8889, data4.c_str(), data2.size());
            }
        }
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what();
    }
}
