#!/bin/bash
clear
cd  /home/adw/Documents/ETH/EtherneProcess/Server
rm -rf server.o
g++ server.cpp -o server.o
# g++ server.cpp -lstdc++ -pthread -o server.o
cd /home/adw/Documents/ETH/EtherneProcess/Client
rm -rf client.o
g++ client.cpp -o client.o
# g++ client.cpp -lstdc++ -pthread -o client.o

cd /home/adw/Documents/ETH/EtherneProcess/Client2
rm -rf client.o
g++ client.cpp -o client.o

cd /home/adw/Documents/ETH/EtherneProcess/Controller
rm -rf controller.o
g++ controller.cpp -o controller.o
exit 0