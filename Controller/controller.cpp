// C++ UDP Transmitter

#include "../UDPNetWork.h"
#include "iostream"

int main()
{
  std::string IP = "127.0.0.1";
  int PORT = 8886;

  try
  {
    UDPSocket Socket;
    std::string data = "\b";
    char buffer[100];

    while (1)
    {
      std::cout << "Enter data to transmit : " << std::endl;
      std::getline(std::cin, data);
      Socket.SendTo(IP, 8886, data.c_str(), data.size());
    }
  }
  catch (std::exception &ex)
  {
    std::cout << ex.what();
  }
}
