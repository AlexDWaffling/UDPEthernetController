// C++ UDP Receiver

#include "../UDPNetWork.h"
#include "iostream"

int main()
{
  int PORT = 8888;

  try
  {
    UDPSocket Socket;
    char buffer[100];

    Socket.Bind(PORT);
    while (1)
    {
      sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
      std::string input(buffer);
      std::cout << "Data received: " << input << std::endl;
    }
  }
  catch (std::system_error& e)
  {
    std::cout << e.what();
  }
}
