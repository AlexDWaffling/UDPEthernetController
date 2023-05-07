// C++ UDP Transmitter

#include "../UDPNetWork.h"
#include "iostream"

int main()
{
  std::string HOST_IP = "192.168.0.10";
  int PORT = 3000;

  try
  {
    UDPSocket Socket;
    std::string data = "\b";
    char buffer[100];

    while (1)
    {
      std::cout << "Enter data to transmit : " << std::endl;
      std::getline(std::cin, data);
      Socket.SendTo(HOST_IP, PORT, data.c_str(), data.size());
    }
  }
  catch (std::exception &ex)
  {
    std::cout << ex.what();
  }
}
