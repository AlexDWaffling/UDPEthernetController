#!/bin/bash
clear
cd Server
rm -rf server.o
g++ -std=c++17 server.cpp -o server.o
# g++ server.cpp -lstdc++ -pthread -o server.o
# cd ../Client
# rm -rf client.o
# g++ -std=c++17 client.cpp -o client.o
# # g++ client.cpp -lstdc++ -pthread -o client.o

# cd ../Client2
# rm -rf client.o
# g++ -std=c++17 client.cpp -o client.o

cd ../Controller
rm -rf controller.o
g++ -std=c++17 controller.cpp -o controller.o
exit 0